#!/usr/local/bin/bash
# -ev negates the regular expression so it will not show up in the logfile window only
# for the file following the command(s). 
# -cS uses the color scheme set in multitail.conf for only the file follwing the command.
# -i specific file to tail.
# -wh window 2's only 12 lines high

# The order of these lines matter as each color scheme and regular expression are tied to
# the file that is being tailed. Everything before each -i is tied to the options before it.
if [ "$#" -eq 0 ];then
    echo "Need a multitail config file naem";
    exit 1;
fi

confpath=$1

multitail --config $confpath \
-f \
-cS syslog \
-ev "last message repeated" \
-ev "load average" \
-i /var/log/messages \
-cS postfix \
-i /var/log/maillog
