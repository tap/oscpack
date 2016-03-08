#pragma once
#include "AbstractUdpSocket.h"

#if defined(_MSC_VER)
#error TODO
#else
#include "posix/UdpSocket.h"
#include "posix/NetworkingUtils.h"
#endif

namespace oscpack
{
namespace detail
{
#if defined(_MSC_VER)
#error TODO
#else
using Implementation = oscpack::posix::Implementation;
#endif
}

using UdpTransmitSocket = detail::UdpTransmitSocket<detail::Implementation>;
using UdpReceiveSocket = detail::UdpReceiveSocket<detail::Implementation>;
using UdpListeningReceiveSocket = detail::UdpListeningReceiveSocket<detail::Implementation>;
}
