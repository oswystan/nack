/*
 **************************************************************************************
 *       Filename:  nack.h
 *    Description:   header file
 *
 *        Version:  1.0
 *        Created:  2019-09-03 11:14:55
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef NACK_H_INCLUDED
#define NACK_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <vector>
class NackModule
{
public:
    NackModule(uint16_t windowSize = kFixedWindow) {
        memset(m_sequenceRecord, 0xff, sizeof(m_sequenceRecord));
        if (windowSize > 0 && windowSize < kMaxRecord) {
            m_window = windowSize;
        }
    }
    virtual ~NackModule () {}

    void HandleSequence(uint16_t seq, std::vector<uint16_t> &nack);
    static bool GreaterThan(uint16_t a, uint16_t b);
    static uint16_t Distance(uint16_t a, uint16_t b) {
        return a - b;
    }

private:
    static const uint16_t kMaxRecord = 256;
    static const uint16_t kFixedWindow = 4;
    static const uint16_t kMaxDistance = (65536 / 2);
    uint16_t m_sequenceRecord[kMaxRecord];
    uint16_t m_firstSequence = 0;
    uint16_t m_lastSequence  = 0;
    uint16_t m_window        = kFixedWindow;
    bool     m_init          = false;
};

#endif /*NACK_H_INCLUDED*/

/********************************** END **********************************************/

