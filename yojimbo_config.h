/*
    Yojimbo Network Library.
    
    Copyright © 2016 - 2017, The Network Protocol Company, Inc.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
           in the documentation and/or other materials provided with the distribution.

        3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
           from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef YOJIMBO_CONFIG_H
#define YOJIMBO_CONFIG_H

/** @file */

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#define YOJIMBO_MAJOR_VERSION 0
#define YOJIMBO_MINOR_VERSION 5
#define YOJIMBO_PATCH_VERSION 0

// Endianness detection from rapidjson
#if !defined(YOJIMBO_LITTLE_ENDIAN) && !defined(YOJIMBO_BIG_ENDIAN)

  #ifdef __BYTE_ORDER__
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      #define YOJIMBO_LITTLE_ENDIAN 1
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      #define YOJIMBO_BIG_ENDIAN 1
    #else
      #error Unknown machine endianess detected. User needs to define YOJIMBO_LITTLE_ENDIAN or YOJIMBO_BIG_ENDIAN.
    #endif // __BYTE_ORDER__
  
  // Detect with GLIBC's endian.h
  #elif defined(__GLIBC__)
    #include <endian.h>
    #if (__BYTE_ORDER == __LITTLE_ENDIAN)
      #define YOJIMBO_LITTLE_ENDIAN 1
    #elif (__BYTE_ORDER == __BIG_ENDIAN)
      #define YOJIMBO_BIG_ENDIAN 1
    #else
      #error Unknown machine endianess detected. User needs to define YOJIMBO_LITTLE_ENDIAN or YOJIMBO_BIG_ENDIAN.
    #endif // __BYTE_ORDER
  
  // Detect with _LITTLE_ENDIAN and _BIG_ENDIAN macro
  #elif defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)
    #define YOJIMBO_LITTLE_ENDIAN 1
  #elif defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)
    #define YOJIMBO_BIG_ENDIAN 1
  
  // Detect with architecture macros
  #elif    defined(__sparc)     || defined(__sparc__)                           \
        || defined(_POWER)      || defined(__powerpc__)                         \
        || defined(__ppc__)     || defined(__hpux)      || defined(__hppa)      \
        || defined(_MIPSEB)     || defined(_POWER)      || defined(__s390__)
    #define YOJIMBO_BIG_ENDIAN 1
  #elif    defined(__i386__)    || defined(__alpha__)   || defined(__ia64)      \
        || defined(__ia64__)    || defined(_M_IX86)     || defined(_M_IA64)     \
        || defined(_M_ALPHA)    || defined(__amd64)     || defined(__amd64__)   \
        || defined(_M_AMD64)    || defined(__x86_64)    || defined(__x86_64__)  \
        || defined(_M_X64)      || defined(__bfin__)
    #define YOJIMBO_LITTLE_ENDIAN 1
  #elif defined(_MSC_VER) && defined(_M_ARM)
    #define YOJIMBO_LITTLE_ENDIAN 1
  #else
    #error Unknown machine endianess detected. User needs to define YOJIMBO_LITTLE_ENDIAN or YOJIMBO_BIG_ENDIAN. 
  #endif
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4127 )
#pragma warning( disable : 4244 )
#endif // #ifdef _MSC_VER

#define YOJIMBO_PLATFORM_WINDOWS                    1
#define YOJIMBO_PLATFORM_MAC                        2
#define YOJIMBO_PLATFORM_UNIX                       3

#if defined(_WIN32)
#define YOJIMBO_PLATFORM YOJIMBO_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define YOJIMBO_PLATFORM YOJIMBO_PLATFORM_MAC
#else
#define YOJIMBO_PLATFORM YOJIMBO_PLATFORM_UNIX
#endif

#define YOJIMBO_SOCKETS                             1

#if !defined( YOJIMBO_SECURE_MODE )
#define YOJIMBO_SECURE_MODE                         0               ///< IMPORTANT: This should be set to 1 in your retail build!
#endif // #if !defined( YOJIMBO_SECURE_MODE )

#define YOJIMBO_SERIALIZE_CHECKS                    1

#ifndef NDEBUG

#define YOJIMBO_DEBUG_MEMORY_LEAKS                  1

#define YOJIMBO_DEBUG_MESSAGE_LEAKS                 1

#define YOJIMBO_VALIDATE_MESSAGE_BUDGET             1

#endif // #ifndef NDEBUG

#define YOJIMBO_DEBUG_SPAM                          0               // todo: would be much nicer to have advanced logging with log levels, as per-netcode.io

#include <stdint.h>
#include <stdlib.h>

/// The library namespace.

namespace yojimbo
{
    const int MaxClients = 64;                                      ///< The maximum number of clients supported by this library. You can increase this if you want, but this library is designed around patterns that work best for [2,64] player games. If your game has less than 64 clients, reducing this will save memory.
    const int MaxChannels = 64;                                     ///< The maximum number of message channels supported by this library. If you need less than 64 channels per-packet, reducing this saves memory.
    const int KeyBytes = 32;                                        ///< Size of encryption key for dedicated client/server in bytes. Do not change.
    const int ConservativeMessageHeaderEstimate = 32;               ///< Conservative message header estimate used when checking that message data fits within the message budget. See YOJIMBO_VALIDATE_MESSAGE_BUDGET
    const int ConservativeFragmentHeaderEstimate = 64;              ///< Conservative fragment header estimate used when checking that message data fits within the message budget. See YOJIMBO_VALIDATE_MESSAGE_BUDGET
    const int ConservativeChannelHeaderEstimate = 32;               ///< Conservative channel header estimate used when checking that message data fits within the message budget. See YOJIMBO_VALIDATE_MESSAGE_BUDGET
    const int ConservativeConnectionPacketHeaderEstimate = 128;     ///< Conservative packet header estimate used when checking that message data fits within the message budget. See YOJIMBO_VALIDATE_MESSAGE_BUDGET
    const uint32_t SerializeCheckValue = 0x12345678;                ///< The value written to the stream for serialize checks. See WriteStream::SerializeCheck and ReadStream::SerializeCheck.

    /// Channel type. Determines the reliability and ordering guarantees for a channel.

    enum ChannelType
    {
        CHANNEL_TYPE_RELIABLE_ORDERED,                              ///< Messages are received reliably and in the same order they were sent. 
        CHANNEL_TYPE_UNRELIABLE_UNORDERED                           ///< Messages are sent unreliably. Messages may arrive out of order, or not at all.

        // todo: add UNRELIABLE_ORDERED, it's a trivial change...
    };

    /** 
        Configuration properties for a message channel.
     
        Channels let you specify different reliability and ordering guarantees for messages sent across a connection.
     
        They may be configured as one of two types: reliable-ordered or unreliable-unordered.
     
        Reliable ordered channels guarantee that messages (see Message) are received reliably and in the same order they were sent. 
        This channel type is designed for control messages and RPCs sent between the client and server.
    
        Unreliable unordered channels are like UDP. There is no guarantee that messages will arrive, and messages may arrive out of order.
        This channel type is designed for data that is time critical and should not be resent if dropped, like snapshots of world state sent rapidly 
        from server to client, or cosmetic events such as effects and sounds.
        
        Both channel types support blocks of data attached to messages (see BlockMessage), but their treatment of blocks is quite different.
        
        Reliable ordered channels are designed for blocks that must be received reliably and in-order with the rest of the messages sent over the channel. 
        Examples of these sort of blocks include the initial state of a level, or server configuration data sent down to a client on connect. These blocks 
        are sent by splitting them into fragments and resending each fragment until the other side has received the entire block. This allows for sending
        blocks of data larger that maximum packet size quickly and reliably even under packet loss.
        
        Unreliable-unordered channels send blocks as-is without splitting them up into fragments. The idea is that transport level packet fragmentation
        should be used on top of the generated packet to split it up into into smaller packets that can be sent across typical Internet MTU (<1500 bytes). 
        Because of this, you need to make sure that the maximum block size for an unreliable-unordered channel fits within the maximum packet size.
        
        Channels are typically configured as part of a ConnectionConfig, which is included inside the ClientServerConfig that is passed into the Client and Server constructors.
     */

    struct ChannelConfig
    {
        ChannelType type;                                           ///< Channel type: reliable-ordered or unreliable-unordered.
        bool disableBlocks;                                         ///< Disables blocks being sent across this channel.
        int sendQueueSize;                                          ///< Number of messages in the send queue for this channel.
        int receiveQueueSize;                                       ///< Number of messages in the receive queue for this channel.
        int sentPacketBufferSize;                                   ///< Maps packet level acks to individual messages & fragments. Please consider your packet send rate and make sure you have at least a few seconds worth of entries in this buffer.
        int maxMessagesPerPacket;                                   ///< Maximum number of messages to include in each packet. Will write up to this many messages, provided the messages fit into the channel packet budget and the number of bytes remaining in the packet.
        int packetBudget;                                           ///< Maximum amount of message data to write to the packet for this channel (bytes). Specifying -1 means the channel can use up to the rest of the bytes remaining in the packet.
        int maxBlockSize;                                           ///< The size of the largest block that can be sent across this channel (bytes).
        int fragmentSize;                                           ///< Blocks are split up into fragments of this size when sent over a reliable-ordered channel (bytes).
        float messageResendTime;                                    ///< Minimum delay between message resends (seconds). Avoids sending the same message too frequently.
        float fragmentResendTime;                                   ///< Minimum delay between fragment resends (seconds). Avoids sending the same fragment too frequently.

        ChannelConfig() : type ( CHANNEL_TYPE_RELIABLE_ORDERED )
        {
            disableBlocks = false;
            sendQueueSize = 1024;
            receiveQueueSize = 1024;
            sentPacketBufferSize = 1024;
            maxMessagesPerPacket = 64;
            packetBudget = 1100;
            maxBlockSize = 256 * 1024;
            fragmentSize = 1024;
            messageResendTime = 0.1f;
            fragmentResendTime = 0.25f;
        }

        int GetMaxFragmentsPerBlock() const
        {
            return maxBlockSize / fragmentSize;
        }
    };

    /** 
        Configures connection properties and the set of channels for sending and receiving messages.
        
        Specifies the maximum packet size to generate, and the number of message channels, and the per-channel configuration data. See ChannelConfig for details.
        
        Typically configured as part of a ClientServerConfig which is passed into Client and Server constructors.
     */

    struct ConnectionConfig
    {
        int connectionPacketType;                               ///< Connection packet type (so you can override it). Only necessary to set this if you are using Connection directly. Not necessary to set when using client/server as it overrides it to CLIENT_SERVER_PACKET_CONNECTION for you automatically.
        int slidingWindowSize;                                  ///< The size of the sliding window used for packet acks (# of packets in history). Depending on your packet send rate, you should make sure this buffer is large enough to cover at least a few seconds worth of packets.
        int maxPacketSize;                                      ///< The maximum size of packets generated to transmit messages between client and server (bytes).
        int numChannels;                                        ///< Number of message channels in [1,MaxChannels]. Each message channel must have a corresponding configuration below.
        ChannelConfig channel[MaxChannels];                     ///< Per-channel configuration. See ChannelConfig for details.

        ConnectionConfig()
        {
            connectionPacketType = 0;
            maxPacketSize = 8 * 1024;
            slidingWindowSize = 1024;
            numChannels = 1;
        }
    };

    /** 
        Configuration shared between client and server.
        
        Passed to Client and Server constructors to configure their behavior.
        
        Please make sure that the message configuration is identical between client and server or it will not work.
     */

    // todo: maybe just inherit from connection config? seems cleaner

    struct BaseClientServerConfig : public ConnectionConfig
    {
        uint64_t protocolId;                                    ///< Clients can only connect to servers with the same protocol id. Use this for versioning.
        int clientMemory;                                       ///< Memory allocated inside Client for packets, messages and stream allocations (bytes)
        int serverGlobalMemory;                                 ///< Memory allocated inside Server for global connection request and challenge response packets (bytes)
        int serverPerClientMemory;                              ///< Memory allocated inside Server for packets, messages and stream allocations per-client (bytes)
        
        BaseClientServerConfig()
        {
            protocolId = 0;
            clientMemory = 2 * 1024 * 1024;
            serverGlobalMemory = 2 * 1024 * 1024;
            serverPerClientMemory = 2 * 1024 * 1024;
        }
    };

    struct ClientServerConfig : public BaseClientServerConfig
    {
        // ...
    };
}

#endif // #ifndef YOJIMBO_CONFIG_H
