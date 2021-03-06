//===-- DTMMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for parseing DTM Messages
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cstring>
#include <cmath>
#include <iostream>

#if 0
| N | Message     |
|---+-------------|
| 1 | W84 Valid   |
| 2 | W72 Invalid |
| 3 | Empty       |
#endif

namespace NMEA {
TEST(DTMMessageParse, Valid_W84_Message) {
  const std::string RawMessage = "$GPDTM,W84,,0.0,N,0.0,E,0.0,W84*6F";

  GPDTM Message{"W84", "", 0.0f, 0.0f, 0.0f, "W84"};

  NMEAMessage Expected = {NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::DTM, 1,
                          &Message};

  auto Parser = HNMEAParser_Create();
  auto Result = HNMEAParser_Parse(Parser, RawMessage.c_str());

  // Compare Header
  EXPECT_EQ(Expected.ID, Result->ID);
  EXPECT_EQ(Expected.Type, Result->Type);
  EXPECT_EQ(Expected.Valid, Result->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
  NMEAMessage_Destroy(Result);
  HNMEAParser_Destroy(Parser);
};

TEST(DTMMessageParse, Valid_W72_Message) {
  const std::string RawMessage = "$GPDTM,W72,,0.00,S,0.01,W,-2.8,W84*4F";

  GPDTM Message{"W72", "", 0.0f, -0.01f, -2.8f, "W84"};

  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::DTM, 1,
                       &Message};

  auto Parser = HNMEAParser_Create();
  auto Result = HNMEAParser_Parse(Parser, RawMessage.c_str());

  // Compare Header
  EXPECT_EQ(Expected.ID, Result->ID);
  EXPECT_EQ(Expected.Type, Result->Type);
  EXPECT_EQ(Expected.Valid, Result->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
  NMEAMessage_Destroy(Result);
  HNMEAParser_Destroy(Parser);
};

TEST(DTMMessageParse, Valid_999_Message) {
  const std::string RawMessage = "$GPDTM,999,CH95,0.08,N,0.07,E,-47.7,W84*1C";

  GPDTM Message{"999", "CH95", 0.08f, 0.07f, -47.7f, "W84"};

  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::DTM, 1,
                       &Message};

  auto Parser = HNMEAParser_Create();
  auto Result = HNMEAParser_Parse(Parser, RawMessage.c_str());

  // Compare Header
  EXPECT_EQ(Expected.ID, Result->ID);
  EXPECT_EQ(Expected.Type, Result->Type);
  EXPECT_EQ(Expected.Valid, Result->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
  NMEAMessage_Destroy(Result);
  HNMEAParser_Destroy(Parser);
};

TEST(DTMMessageParse, Invalid_Message) {
  const std::string RawMessage = "asdfliouieniifioewufyshdfj";

  NMEAMessage Expected{NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       0,
                       {}};

  auto Parser = HNMEAParser_Create();
  auto Result = HNMEAParser_Parse(Parser, RawMessage.c_str());

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.DTM, Result->DTM);
  NMEAMessage_Destroy(Result);
  HNMEAParser_Destroy(Parser);
}

TEST(DTMMessageParse, Empty_Message) {
  const std::string RawMessage = "";

  NMEAMessage Expected{NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       0,
                       {}};

  auto Parser = HNMEAParser_Create();
  auto Result = HNMEAParser_Parse(Parser, RawMessage.c_str());

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.DTM, Result->DTM);
  NMEAMessage_Destroy(Result);
  HNMEAParser_Destroy(Parser);
}
}
