# Bachelor project: Detection of air shower profiles with the Cherenkov Telescope Array

## Description:
The Cherenkov Telescope Array (CTA) is the next generation ground-based observatory for gamma-ray astronomy at very-high energies. With several tens of telescopes located in the northern and southern hemispheres, CTA will be the world’s largest and most sensitive high-energy gamma-ray observatory. This project aims at developing an analysis chain to allow CTA to be also a cosmic-ray (CR) experiment in the TeV energy range.

The longitudinal development of air showers generated by gamma-rays and CR can be reconstructed by CTA using a fit of a trial function. By this fit, it is possible to get an important parameter like the maximum depth of the shower in atmosphere, which is commonly used for the mass composition of CR. In this project, we propose the study of two kinds of trial function, Gaisser-Hillas and Gaussian in age, to be tested on a set of simulated showers. The goal is to investigate which function describes better the different kind of shower profiles.

## ROOT tutorial

The tutorial1 folder contains a data folder with the root files of air shower profiles and an introduction to ROOT split in two parts:
- First part contains macro scripts for creating TGraph, TH1D, TTree, etc.
- Second part contains scripts to read the simulations files and plot TGraph of the air showers profiles.

