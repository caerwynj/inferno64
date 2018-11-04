#!/usr/bin/env python

import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:
        sys.stderr.write("Usage: %s <configuration file>\n" % sys.argv[0])
        sys.stderr.write("Patches the configuration file; e.g. os/pc/pc\n\n")
        sys.exit(1)
    
    config_file = sys.argv[1]
    
    try:
        t = open(config_file).read()
        t = t.replace("\t/n\n", "\t/n\t/\n")
        t = t.replace("\t/n/remote\n", "\t/n/remote\t/\n")
        t = t.replace("wminit", "shell")
        t = t.replace("consoleprint=0", "consoleprint=1")
        t += "\t/dis/lib/arg.dis\n"
        t += "\t/dis/lib/filepat.dis\n"
        open(config_file, "w").write(t)
    except IOError:
        sys.stderr.write("Failed to fix configuration file '%s'.\n" % config_file)
        sys.exit(1)
    
    sys.exit()


