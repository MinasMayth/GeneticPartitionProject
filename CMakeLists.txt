cmake_minimum_required(VERSION 3.0)
project(GeneticPartition C)

set(CMAKE_C_STANDARD 99)

add_executable(GeneticPartition main.c GeneticPartitionCore.c GeneticPartitionCore.h GeneticPartitionVisualization.c GeneticPartitionVisualization.h Testing.c Testing.h
        GeneticPartitionConfigurationSettings.c GeneticPartitionConfigurationSettings.h)
