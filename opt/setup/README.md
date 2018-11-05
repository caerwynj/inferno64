# Description

Scripts to setup projects installed in `/opt` (bind their commands, man
pages, etc. to standard places).


# Install

Make directory with these scripts available in /opt/setup/.

Install system-wide:

```
# git clone https://github.com/powerman/inferno-opt-setup.git $INFERNO_ROOT/opt/setup
```

or in your home directory:

```
$ git clone https://github.com/powerman/inferno-opt-setup.git $INFERNO_USER_HOME/opt/setup
$ emu
; bind opt /opt
```


# Usage

Add this into `profile` file in your Inferno home dir:

```
/opt/setup/cmd
/opt/setup/man
```

The `/opt/setup/cmd` will bind all commands provided by /opt packages into
`/dis/`, to let you run these commands by their name, without long
`/opt/provider/package/dis/cmd/` prefix.

The `/opt/setup/man` will bind all man pages provided by /opt packages
into `/man/*/` and union provided man indexes with `/man/*/INDEX`.

