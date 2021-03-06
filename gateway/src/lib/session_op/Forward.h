//
// Copyright 2016 - 2020 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include <cstdint>
#include <list>

#include "comms/util/ScopeGuard.h"
#include "SessionOp.h"
#include "common.h"

namespace mqttsn
{

namespace gateway
{

namespace session_op
{

class Forward : public SessionOp
{
    typedef SessionOp Base;

public:
    Forward(SessionState& sessionState);
    ~Forward();

protected:

private:
    using Base::handle;
    virtual void handle(PublishMsg_SN& msg) override;
    virtual void handle(PubrelMsg_SN& msg) override;
    virtual void handle(PingreqMsg_SN& msg) override;
    virtual void handle(PingrespMsg_SN& msg) override;
    virtual void handle(SubscribeMsg_SN& msg) override;
    virtual void handle(UnsubscribeMsg_SN& msg) override;

    virtual void handle(ConnackMsg& msg) override;
    virtual void handle(PubackMsg& msg) override;
    virtual void handle(PubrecMsg& msg) override;
    virtual void handle(PubcompMsg& msg) override;
    virtual void handle(PingreqMsg& msg) override;
    virtual void handle(PingrespMsg& msg) override;
    virtual void handle(SubackMsg& msg) override;
    virtual void handle(UnsubackMsg& msg) override;

    struct SubInfo
    {
        Timestamp m_timestamp = 0U;
        std::uint16_t m_msgId = 0;
        std::uint16_t m_topicId = 0;
    };

    typedef std::list<SubInfo> SubsInProgressList;

    struct NoGwPubInfo
    {
        std::uint16_t m_topicId = 0;
        DataBuf m_data;
    };

    typedef std::list<NoGwPubInfo> NoGwPubInfosList;

    using ReturnCodeVal = mqttsn::field::ReturnCodeVal;
    using TopicIdTypeVal = mqttsn::field::FlagsMembersCommon::TopicIdTypeVal;
    void sendPubackToClient(
        std::uint16_t topicId,
        std::uint16_t msgId,
        ReturnCodeVal rc);


    std::uint16_t m_lastPubTopicId = 0;
    bool m_pingInProgress = false;
    SubsInProgressList m_subs;
    NoGwPubInfosList m_pubs;
};

}  // namespace session_op

}  // namespace gateway

}  // namespace mqttsn


