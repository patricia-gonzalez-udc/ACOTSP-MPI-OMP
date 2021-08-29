#!/bin/bash
#SBATCH -n 6
#SBATCH --ntasks-per-node=6
#SBATCH -c 4
#SBATCH -p thinnodes
#SBATCH -t 00:30:00

module load intel impi

export HOME=/home/ulc/es/pgg/ACOTSP-MPI-OMP
export NUM_PROC_MPI=6
export OMP_NUM_THREADS=4

srun $HOME/acotsp -i pr2392.tsp -r 10 -t 100. -x -o 378032  
