/*
 **************************************************************************************
 *       Filename:  nack.cc
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2019-09-03 11:15:11
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#include "nack.h"

void NackModule::HandleSequence(uint16_t seq, std::vector<uint16_t> &nack) {
    nack.clear();

    // record seq and init first & last sequence
    m_sequenceRecord[seq % kMaxRecord] = seq;
    if (!m_init) {
        m_firstSequence = m_lastSequence = seq;
        m_init = true;
        return;
    }

    // reset last & first sequence according current input seq
    if (GreaterThan(seq, m_lastSequence)) {
        m_lastSequence = seq;
    } else if (!GreaterThan(seq, m_firstSequence)) {
        m_firstSequence = seq;
    }

    // check distance and reset first sequence
    uint16_t val = Distance(m_lastSequence, m_firstSequence);
    if (val > kMaxRecord) {
        m_firstSequence = m_lastSequence - kMaxRecord;
    } else if (val <= m_window) {
        return;
    }

    // generate nack list
    uint16_t sequence = 0;
    uint16_t i;
    for (i = 0; i < val - m_window; ++i) {
        sequence = (uint16_t)(m_firstSequence + i);
        if (m_sequenceRecord[sequence % kMaxRecord] != sequence) {
            nack.push_back(sequence);
        }
    }
    return;
}

// compare sequence number
bool NackModule::GreaterThan(uint16_t a, uint16_t b) {
    if (a == b) {
        return false;
    }
    if (uint16_t(a - b) >= kMaxDistance) {
        return false;
    } else {
        return true;
    }
}

/********************************** END **********************************************/

