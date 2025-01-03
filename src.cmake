# add the root of this source tree to the include path
include_directories(
    ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src
)

set(
    LIBRARY_SOURCE_FILES
    src/controllers/GenericDescriptor.cpp
    src/controllers/GenericMulticastUdp.cpp
    src/controllers/MulticastUdpReceiver.cpp
    src/controllers/MulticastUdpTransmitter.cpp
    src/controllers/threads/MainThread.cpp
    src/models/ByteArray.cpp
    src/models/CommandlineArguments.cpp
    src/models/DnsMessageType.cpp
    src/models/DnsResourceType.cpp
    src/models/GenericMdnsRecord.cpp
    src/models/IpProtocol.cpp
    src/models/LogLevel.cpp
    src/models/MdnsMessage.cpp
    src/models/MdnsQueryRecord.cpp
    src/models/MdnsResourceRecord.cpp
    src/models/MulticastMessage.cpp
    src/models/StringList.cpp
    src/models/resource-record-payload/GenericResourceRecordPayload.cpp
    src/models/resource-record-payload/ResourceRecordAPayload.cpp
    src/models/resource-record-payload/ResourceRecordPtrPayload.cpp
    src/models/resource-record-payload/ResourceRecordSrvPayload.cpp
    src/models/resource-record-payload/ResourceRecordTxtPayload.cpp
    src/protocols/ByteArray.cpp
    src/protocols/DnsMessageType.cpp
    src/protocols/DnsResourceType.cpp
    src/protocols/GenericMdnsRecord.cpp
    src/protocols/IpProtocol.cpp
    src/protocols/LogLevel.cpp
    src/protocols/MdnsMessage.cpp
    src/protocols/MdnsQueryRecord.cpp
    src/protocols/MdnsResourceRecord.cpp
    src/protocols/StringList.cpp
    src/protocols/resource-record-payload/GenericResourceRecordPayload.cpp
    src/protocols/resource-record-payload/ResourceRecordAPayload.cpp
    src/protocols/resource-record-payload/ResourceRecordPtrPayload.cpp
    src/protocols/resource-record-payload/ResourceRecordSrvPayload.cpp
    src/protocols/resource-record-payload/ResourceRecordTxtPayload.cpp
    src/utils/CommandlineParser.cpp
    src/utils/Containers.cpp
    src/utils/Conversion.cpp
    src/utils/Join.cpp
    src/utils/Log.cpp
    src/utils/Trim.cpp
    src/utils/Split.cpp
)

add_library(
    libspotify-connect-proxy
    ${LIBRARY_SOURCE_FILES}
)

# extra compiler options
target_compile_options(
    libspotify-connect-proxy
    PRIVATE
    -Wall -Werror
)

add_executable(
    spotify-connect-proxy
    src/SpotifyConnectProxy.cpp
)

# extra compiler options
target_compile_options(
    spotify-connect-proxy
    PRIVATE
    -Wall -Werror
)

target_link_libraries(
    spotify-connect-proxy
    libspotify-connect-proxy
    PkgConfig::SYSTEMD
)

# install binaries to the target
install(
    TARGETS
    spotify-connect-proxy
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
