Binaries for Bitcoin5000 version 0.3.21 are available at:
  https://sourceforge.net/projects/bitcoin5000/files/Bitcoin5000/bitcoin5000-0.3.21/

Changes and new features from the 0.3.20 release include:

* Universal Plug and Play support.  Enable automatic opening of a port for incoming connections by running bitcoin5000 or bitcoin5000d with the - -upnp=1 command line switch or using the Options dialog box.

* Support for full-precision bitcoin5000 amounts.  You can now send, and bitcoin5000 will display, bitcoin5000 amounts smaller than 0.01.  However, sending fewer than 0.01 bitcoin5000s still requires a 0.01 bitcoin5000 fee (so you can send 1.0001 bitcoin5000s without a fee, but you will be asked to pay a fee if you try to send 0.0001).

* A new method of finding bitcoin5000 nodes to connect with, via DNS A records. Use the -dnsseed option to enable.

For developers, changes to bitcoin5000's remote-procedure-call API:

* New rpc command "sendmany" to send bitcoin5000s to more than one address in a single transaction.

* Several bug fixes, including a serious intermittent bug that would sometimes cause bitcoin5000d to stop accepting rpc requests. 

* -logtimestamps option, to add a timestamp to each line in debug.log.

* Immature blocks (newly generated, under 120 confirmations) are now shown in listtransactions.
