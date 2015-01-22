# sysinfo-utils
Mini utilities for spitting out system information. 

- `active-ip4` - return first ip address available from a list of interfaces.

   Ex: on a machine with three interfaces, `eth0`, `eth1` and `wlan0`, of
   which only `eth1` and `wlan0` are connected with ips `192.168.1.72` and
   `192.168.1.150`, respectively.

        $ active-ip4 eth0 eth1 wlan0
        192.168.1.72
        $
