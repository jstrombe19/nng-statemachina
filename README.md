# nng-statemachina
FSM using NNG to send/receive state updates


### Implementation Objectives

Create a simple finite state machine that maintains correct information about the state of the applications
over which it presides. The updates to a dependent application's state will be passed to the presiding 
application via [nng](https://github.com/nanomsg/nng).

The baseline implementation supports using the request/response nng protocol; however, future iterations 
may update that interface to be a two-way radio, depending on the outcome of initial testing that will 
determine the delay time between pushing a state change command and querying the state of the dependent 
application(s). {PUSH from dependent applications | PULL from supervising application}

The application for this proof of concept is intended to be an autonomous-capable rover. The rover will 
support direct user control and manipulation, but will also be capable of handling fully autonomous task-
execution and decision-making based on parameters provided. The inspiration behind this is JPL's 
[Curiosity](https://www.jpl.nasa.gov/missions/mars-science-laboratory-curiosity-rover-msl) rover, sent to Mars in 2012.

Current punchlist items are as follows:
[] Create a baseline supervisory application
[] Create a dependent application template
[] Create multiple dependent applications
[] Create unique telemetry data points for each dependent application
[] Create the stateful awareness of each dependent application in the supervisory application
[] Break the dependent applications' req/resp handler into a dedicated thread to free up its execution
[] Generate telemetry data from each application
[] Tie telemetry data points to a config file
[] Tie the socket handle to a config file
[] Explore pub/sub and two-way radio protocols
[] Incorporate spdlog
[] Incorporate file processing
[] Incorporate file encryption (that can be enabled/disabled)
[] Incorporate a GUI that exposes the state of all applications
[] Create a schedule manager (wrapper for [cron](https://opensource.com/article/22/3/scheduling-tasks-linux-cron) / [systemd](https://trstringer.com/systemd-timer-vs-cronjob/) / <>)
[] Export logging on a regular cadence
[] Incorporate GPS/GNSS


##### STRETCH GOALS

[] Cross-compile for Raspberry Pi 4
[] Cross-compile for Dragonboard 410C
[] Cross-compile for Beaglebone AI