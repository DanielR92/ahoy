//-----------------------------------------------------------------------------
// 2022 Ahoy, https://github.com/lumpapu/ahoy
// Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//-----------------------------------------------------------------------------

#ifndef __HM_SYSTEM_H__
#define __HM_SYSTEM_H__

#include "hmInverter.h"
#include "hmRadio.h"

template <uint8_t MAX_INVERTER=3, class INVERTERTYPE=Inverter<float>>
class HmSystem {
    public:
        HmRadio<> Radio;

        HmSystem() {}

        void setup() {
            mNumInv = 0;
            Radio.setup();
        }

        void setup(uint8_t ampPwr, uint8_t irqPin, uint8_t cePin, uint8_t csPin, uint8_t sclkPin, uint8_t mosiPin, uint8_t misoPin) {
            mNumInv = 0;
            Radio.setup(ampPwr, irqPin, cePin, csPin, sclkPin, mosiPin, misoPin);
        }

        void addInverters(cfgInst_t *config) {
            Inverter<> *iv;
            for (uint8_t i = 0; i < MAX_NUM_INVERTERS; i++) {
                iv = addInverter(&config->iv[i]);
                if (0ULL != config->iv[i].serial.u64) {
                    if (NULL != iv) {
                        DPRINT(DBG_INFO, "added inverter ");
                        if(iv->config->serial.b[5] == 0x11)
                            DBGPRINT("HM");
                        else {
                            DBGPRINT(((iv->config->serial.b[4] & 0x03) == 0x01) ? " (2nd Gen) " : " (3rd Gen) ");
                        }

                        DBGPRINTLN(String(iv->config->serial.u64, HEX));

                        if((iv->config->serial.b[5] == 0x10) && ((iv->config->serial.b[4] & 0x03) == 0x01))
                            DPRINTLN(DBG_WARN, F("MI Inverter are not fully supported now!!!"));
                    }
                }
            }
        }

        INVERTERTYPE *addInverter(cfgIv_t *config) {
            DPRINTLN(DBG_VERBOSE, F("hmSystem.h:addInverter"));
            if(MAX_INVERTER <= mNumInv) {
                DPRINT(DBG_WARN, F("max number of inverters reached!"));
                return NULL;
            }
            INVERTERTYPE *p = &mInverter[mNumInv];
            p->id         = mNumInv;
            p->config     = config;
            DPRINT(DBG_VERBOSE, "SERIAL: " + String(p->config->serial.b[5], HEX));
            DPRINTLN(DBG_VERBOSE, " " + String(p->config->serial.b[4], HEX));
            if((p->config->serial.b[5] == 0x11) || (p->config->serial.b[5] == 0x10)) {
                switch(p->config->serial.b[4]) {
                    case 0x22:
                    case 0x21: p->type = INV_TYPE_1CH; break;
                    case 0x42:
                    case 0x41: p->type = INV_TYPE_2CH; break;
                    case 0x62:
                    case 0x61: p->type = INV_TYPE_4CH; break;
                    default:
                        DPRINTLN(DBG_ERROR, F("unknown inverter type"));
                        break;
                }

                if(p->config->serial.b[5] == 0x11)
                    p->ivGen = IV_HM;
                else if((p->config->serial.b[4] & 0x03) == 0x02) // MI 3rd Gen -> same as HM
                    p->ivGen = IV_HM;
                else // MI 2nd Gen
                    p->ivGen = IV_MI;
            }
            else if(p->config->serial.u64 != 0ULL)
                DPRINTLN(DBG_ERROR, F("inverter type can't be detected!"));

            p->init();

            mNumInv ++;
            return p;
        }

        INVERTERTYPE *findInverter(uint8_t buf[]) {
            DPRINTLN(DBG_VERBOSE, F("hmSystem.h:findInverter"));
            INVERTERTYPE *p;
            for(uint8_t i = 0; i < mNumInv; i++) {
                p = &mInverter[i];
                if((p->config->serial.b[3] == buf[0])
                    && (p->config->serial.b[2] == buf[1])
                    && (p->config->serial.b[1] == buf[2])
                    && (p->config->serial.b[0] == buf[3]))
                    return p;
            }
            return NULL;
        }

        INVERTERTYPE *getInverterByPos(uint8_t pos, bool check = true) {
            DPRINTLN(DBG_VERBOSE, F("hmSystem.h:getInverterByPos"));
            if(pos >= MAX_INVERTER)
                return NULL;
            else if((mInverter[pos].initialized && mInverter[pos].config->serial.u64 != 0ULL) || false == check)
                return &mInverter[pos];
            else
                return NULL;
        }

        uint8_t getNumInverters(void) {
            /*uint8_t num = 0;
            INVERTERTYPE *p;
            for(uint8_t i = 0; i < MAX_NUM_INVERTERS; i++) {
                p = &mInverter[i];
                if(p->config->serial.u64 != 0ULL)
                    num++;
            }
            return num;*/
            return MAX_NUM_INVERTERS;
        }

        void enableDebug() {
            Radio.enableDebug();
        }

    private:
        INVERTERTYPE mInverter[MAX_INVERTER];
        uint8_t mNumInv;
};

#endif /*__HM_SYSTEM_H__*/
