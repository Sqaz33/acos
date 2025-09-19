# Socket

* File desc. for input/output
* Distinct server process which manages connection name
* Several client process which connects to server using common name
* Socket name families:
  * Unix: local file of special type 'socket'
  * ip4 ip6: address + port
  * RAW Packet: network card name

# Create socket

![1758277891302](images/theory/1758277891302.png)

# Socket settings

### Client role:

* Connect ot server process using `connect` system call

### Server role:

* Announce name to allow connection using `bind`
* Create listen queue using `listen` system call
* Accept incoming connection using `accept` system call

![1758278538790](images/theory/1758278538790.png)

![1758278692801](images/theory/1758278692801.png)


# Network

## ARP (Address Resolution Protocol)
