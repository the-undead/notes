# Networking


## Programs

### ip utility (iproute2-7.0.0)

#### interface / link / addr 

show ip link : `ip -br link (device)`
show ip addresses : `ip -br a`
show ip statistics for link : `ip -s link`
set device up/down : `ip link set dev eth0 up/down`
set device mtu : `ip link set dev eth0 mtu 9000`
create virtual ethernet device : `ip link add name veth0 type veth peer name veth1`
create bridge interface : `ip link add br0 type bridge`
 : `ip link set eth0 master br0`
create wireguard device : `ip link add wg0 type wireguard`

add ip address to device: `ip addr add 192.168.1.1/24 dev eth0`
delete ip address for device : `ip addr del 192.168.1.1/24 dev eth0`
remove configuration for device eth0 : `ip addr flush dev eth0`

#### ip routing (Forwarding Information Base)

show routes : `ip route show`
show routes including all tables: `ip route show table all`
get route for an ip: `ip route get 8.8.8.8`

add route: `ip route add 10.0.0.0/24 via 192.168.1.254 dev eth0`
add default route : `ip route add default via 192.168.1.1`
delete a route : `ip route del 10.0.0.0/24`

install a route for ip that has multiple equal-cost next-hops (Equal-Cost Multi-Path - ECMP), bigger number (1-255) means higher weight: `ip route add 10.0.0.0/24 nexthop via 1.1.1.1 weight 1 nexthop via 2.2.2.2 weight 1`

FIB level drops:
blackhole all traffic towards 10.0.0.0/24 : `ip route add blackhole 10.0.0.0/24`
send icmp error to traffic going towards 10.0.0.0/24: `ip route add unreachable 10.0.0.0/24`

#### policy-based routing (pbr)
show ip rules: `ip rule show`
add a rule, traffic coming from ip get's checked against routing table 100: `ip rule add from 192.168.2.0/24 table 100`
add rule that packages marked with `0x1` should use table 100 instead of main routing table: `ip rule add fwmark 0x1 table 100`
add default route for table 100: `ip route add default via 10.0.0.1 table 100`

> the mark (fwmark) is a metadata field attached to a packet inside the kernel (it’s not part of the IP header, it never leaves the box), and it’s typically set by netfilter.

Perform a full routing decision lookup in the FIB for a packet destined for 8.8.8.8, pretending it came from 192.168.2.10 on interface eth0: `ip route get 8.8.8.8 from 192.168.2.10 iif eth0`

#### arp 

Show arp table (kernel's neighbor table): `ip neigh show`
Flush arp table : `ip neigh flush all`
create a permanent neighbor entry: `ip neigh add 192.168.1.10 lladdr aa:bb:cc:dd:ee:ff dev eth0 nud permanent`

## ss

## Connection Types

### DSL

#### Super Vectoring

### FIBER

###
