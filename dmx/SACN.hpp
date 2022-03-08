#include "DMX.hpp"
#include "../3rdparty/libe131/e131.h"
#include <string>

namespace beans {
    enum class E131ErrorCode {
        Success,
        SocketInitErr,
        SourceNameTooLong,
        SetUnicastDestFailed
    };

    class SACNInterface : public DMXInterface {
        public:
            SACNInterface(std::string source_name, std::string dest, uint16_t universe);

            bool Send(UniverseData data);
            E131ErrorCode err;
        
        private:
            int sockfd;
            e131_packet_t packet;
            e131_addr_t dest;
    };
}