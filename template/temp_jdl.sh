#!/bin/sh

#define parameters which are passed in.
path=$1
particle=$2
energy=$3
event=$4
tag=$5
#define the template.
cat  << EOF
universe = vanilla
Executable = condor-executable_${energy}GeV_${particle}_N${event}_${tag}.sh
should_transfer_files = NO
Requirements = TARGET.FileSystemDomain == "privnet"
minute = 60
on_exit_hold =   (ExitCode != 0)
on_exit_remove =   (ExitCode == 0)
periodic_release = NumJobStarts<3 && (CurrentTime - JobCurrentStartDate) >= 30 * \$(MINUTE)
job_machine_attrs = Machine
job_machine_attrs_history_length = 3
requirements = target.machine =!= MachineAttrMachine1 && target.machine =!= MachineAttrMachine2
Output = ${path}/condor_output/sce_\$(cluster)_\$(process).stdout
Error =  ${path}/condor_output/sce_\$(cluster)_\$(process).stderr
Log =    ${path}/condor_output/sce_\$(cluster)_\$(process).condor
Arguments = SCE
Queue 1
EOF
