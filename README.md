# sigwrap

*sigwrap* is a simple wrapper executable for processes such as qemu-kvm which do not respond to SIGINT correctly.  qemu-kvm incorrectly "swallows" SIGINT signals, so that when a user presses CTRL+C at a console when the process is running, the process exits but its wrapper scripts do not (when they should).  See [here](http://stackoverflow.com/questions/18477785/bash-why-does-parent-script-not-terminate-on-sigint-when-child-script-traps-sig/) for more information.

*sigwrap* also forwards any SIGTERM signals that it receives to its child.
