set(
    UNITTEST_SOURCE_FILES
    unittest/models/DnsMessageTypeTest.cpp
    unittest/models/DnsResourceTypeTest.cpp
    unittest/models/IpProtocolTest.cpp
    unittest/models/LogLevelTest.cpp
    unittest/models/MdnsQueryRecordTest.cpp
    unittest/models/MdnsResourceRecordTest.cpp
    unittest/models/MulticastMessageTest.cpp
    unittest/models/resource-record-payload/GenericResourceRecordPayloadTest.cpp
    unittest/models/resource-record-payload/ResourceRecordAPayloadTest.cpp
    unittest/models/resource-record-payload/ResourceRecordPtrPayloadTest.cpp
    unittest/models/resource-record-payload/ResourceRecordSrvPayloadTest.cpp
    unittest/models/resource-record-payload/ResourceRecordTxtPayloadTest.cpp
    unittest/protocols/ByteArrayTest.cpp
    unittest/protocols/DnsMessageTypeTest.cpp
    unittest/protocols/DnsResourceTypeTest.cpp
    unittest/protocols/IpProtocolTest.cpp
    unittest/protocols/LogLevelTest.cpp
    unittest/protocols/StringListTest.cpp
    unittest/protocols/resource-record-payload/ResourceRecordAPayloadTest.cpp
    unittest/protocols/resource-record-payload/ResourceRecordPtrPayloadTest.cpp
    unittest/protocols/resource-record-payload/ResourceRecordSrvPayloadTest.cpp
    unittest/protocols/resource-record-payload/ResourceRecordTxtPayloadTest.cpp
    unittest/utils/CommandlineParserTest.cpp
    unittest/utils/ContainersTest.cpp
    unittest/utils/ConversionTest.cpp
    unittest/utils/EnumMapperTest.cpp
    unittest/utils/JoinTest.cpp
)

add_executable(
    gtest
    EXCLUDE_FROM_ALL

    ${LIBRARY_SOURCE_FILES}
    ${UNITTEST_SOURCE_FILES}

    unittest/gtest_main.cc
)

# extra compiler options
target_compile_options(
    gtest
    PRIVATE
    -DHAVE_CONFIG_H
    -Wall -Werror
    -fPIC
    -O0 -g -coverage
)

target_link_libraries(
    gtest
    PkgConfig::GTEST
    -coverage
)

# when a target "check" exists the unittests will be automatically run on building the Debian package
if (GCOVR)
    add_custom_target(
        check
        gtest
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND
            ${GCOVR} ${CMAKE_BINARY_DIR} -r ${CMAKE_SOURCE_DIR}/src/ -s -j 4 --html --html-details
            --html-medium-threshold 95 --html-high-threshold 100 -o ${CMAKE_BINARY_DIR}/coverage.html
    )
else ()
    add_custom_target(
        check
        gtest
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif ()
