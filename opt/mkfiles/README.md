# Description

These mkfiles can be used as is or as basis for your own mkfiles. Unlike
standard files in `/mkfiles` these know how to handle `/opt` packages;
able to build/run tests (both in host os and inside emu) and have other
features (generation of INDEX files for your man pages, generation of man
pages from text in asciidoc markup, etc.).


# Install

Make directory with these files available in /opt/mkfiles.

Install system-wide:

```
# git clone https://github.com/powerman/inferno-opt-mkfiles.git $INFERNO_ROOT/opt/mkfiles
```

or in your home directory:

```
$ git clone https://github.com/powerman/inferno-opt-mkfiles.git $INFERNO_USER_HOME/opt/mkfiles
$ emu
; bind opt /opt
```

or locally for your project:

```
$ git clone https://github.com/powerman/inferno-opt-mkfiles.git $YOUR_PROJECT_DIR/opt/mkfiles
$ emu
; cd $YOUR_PROJECT_DIR_INSIDE_EMU
; bind opt /opt
```


# Usage

Start your new project using these mkfiles:

```
$ emu
; mkdir newproject
; cd newproject
; cp /opt/mkfiles/mkconfig-example mkconfig
; cp /opt/mkfiles/mkfile-example mkfile
```

