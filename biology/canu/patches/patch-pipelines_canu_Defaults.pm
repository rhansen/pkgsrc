$NetBSD: patch-pipelines_canu_Defaults.pm,v 1.1 2019/01/07 02:33:17 bacon Exp $

# Add resource limits for SLURM
# Upstream is considering a scheduler-independent approach to this feature

--- pipelines/canu/Defaults.pm.orig	2018-06-22 08:20:52.000000000 +0000
+++ pipelines/canu/Defaults.pm
@@ -812,6 +812,16 @@ sub setDefaults () {
     setDefault("gridEngineArraySubmitID",             undef, "Grid engine configuration, not documented");
     setDefault("gridEngineJobID",                     undef, "Grid engine configuration, not documented");
 
+    #####  Slurm-specific parameters for controlling the number of
+    #####  cores / tasks dispatched per step or globally (WIP)
+
+    setDefault( 'slurmCormhapCoreLimit', undef, 'Maximum number of cores allocated for MHAP pre-computing and alignment within the correction phase' );
+    setDefault( 'slurmOvbCoreLimit', undef, 'Maximum number of single-core tasks dispatched for the ovlStore bucketizing step within the trimming phase' );
+    setDefault( 'slurmOvsCoreLimit', undef, 'Maximum number of single-core tasks dispatched for the ovlStore sorting step within the trimming phase' );
+    setDefault( 'slurmRedCoreLimit', undef, 'Maximum number of cores allocated for read error detection within the unitigging phase' );
+    setDefault( 'slurmArrayTaskLimit', undef, 'Maximum number of tasks permitted for each step throughout assembly' );
+    setDefault( 'slurmArrayCoreLimit', undef, 'Maximum number of cores allocated for each step throughout assembly' );
+
     #####  Grid Engine Pipeline
 
     setDefault("useGrid", 1, "If 'true', enable grid-based execution; if 'false', run all jobs on the local machine; if 'remote', create jobs for grid execution but do not submit; default 'true'");
