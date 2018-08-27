Sample init scripts and service configuration for bitcoin5000d
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/bitcoin5000d.service:    systemd service unit configuration
    contrib/init/bitcoin5000d.openrc:     OpenRC compatible SysV style init script
    contrib/init/bitcoin5000d.openrcconf: OpenRC conf.d file
    contrib/init/bitcoin5000d.conf:       Upstart service configuration file
    contrib/init/bitcoin5000d.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "bitcoin5000" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes bitcoin5000d will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, bitcoin5000d requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, bitcoin5000d will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that bitcoin5000d and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If bitcoin5000d is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running bitcoin5000d without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/bitcoin5000.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/bitcoin5000d`  
Configuration file:  `/etc/bitcoin5000/bitcoin5000.conf`  
Data directory:      `/var/lib/bitcoin5000d`  
PID file:            `/var/run/bitcoin5000d/bitcoin5000d.pid` (OpenRC and Upstart) or `/var/lib/bitcoin5000d/bitcoin5000d.pid` (systemd)  
Lock file:           `/var/lock/subsys/bitcoin5000d` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the bitcoin5000 user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
bitcoin5000 user and group.  Access to bitcoin5000-cli and other bitcoin5000d rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/bitcoin5000d`  
Configuration file:  `~/Library/Application Support/Bitcoin5000/bitcoin5000.conf`  
Data directory:      `~/Library/Application Support/Bitcoin5000`
Lock file:           `~/Library/Application Support/Bitcoin5000/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start bitcoin5000d` and to enable for system startup run
`systemctl enable bitcoin5000d`

4b) OpenRC

Rename bitcoin5000d.openrc to bitcoin5000d and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/bitcoin5000d start` and configure it to run on startup with
`rc-update add bitcoin5000d`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop bitcoin5000d.conf in /etc/init.  Test by running `service bitcoin5000d start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy bitcoin5000d.init to /etc/init.d/bitcoin5000d. Test by running `service bitcoin5000d start`.

Using this script, you can adjust the path and flags to the bitcoin5000d program by
setting the BITCOIN5000D and FLAGS environment variables in the file
/etc/sysconfig/bitcoin5000d. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.bitcoin5000.bitcoin5000d.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.bitcoin5000.bitcoin5000d.plist`.

This Launch Agent will cause bitcoin5000d to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run bitcoin5000d as the current user.
You will need to modify org.bitcoin5000.bitcoin5000d.plist if you intend to use it as a
Launch Daemon with a dedicated bitcoin5000 user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
