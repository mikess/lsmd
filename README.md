Linux Service Management Daemon
====

A lightweight service management daemon for linuxi based on System V Init.

Features:
====

1. Managing services by CLI.

2. Monitoring and do define action by service status.

3. Grouping service by type (system, applications, network, user, database).

4. Possibility of communication between servers (basic service HA feature) -
   sending status of service and making scenario.

5. Creating instances of services eg. you can create a several instances of
   httpd for several users.

6. Allow user to create services and instances of application (branch in /applications)
   with user privileges (running services as user).


Why based on System V Init?
===
Because it's compatible with all modern *NIX systems. 


