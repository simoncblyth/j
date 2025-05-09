#
# 2025/05/08
# Dingyong Yang @ IHEP
# yangdy@ihep.ac.cn
# Please read it and change the paths to yours before use it
# If figs are strange, try to change y limit by using set_ylim
#

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
from glob import glob
import os

# Set font
fm.fontManager.addfont("/home/prinks/toolkits/ttfs/Times_New_Roman.ttf")

plt.rcParams['font.family'] = 'Times New Roman'
plt.rcParams['font.size'] = 10
plt.rcParams['axes.titlesize'] = 12
plt.rcParams['axes.labelsize'] = 11
plt.rcParams['xtick.labelsize'] = 10
plt.rcParams['ytick.labelsize'] = 10
plt.rcParams['legend.fontsize'] = 10

# Modified data loading section
def load_all_data(base_pattern):
    """Load all data from files matching the base pattern"""
    all_hits = []
    lengths = []
    for filepath in sorted(glob(base_pattern)):
        data = np.load(filepath)
        all_hits.append(data)
        lengths.append(len(data))
    return np.vstack(all_hits), np.array(lengths)

# Load data from all A and B directories
hits_opticks, lengths_opticks = load_all_data('ALL0_no_opticks_event_name/A*/hit.npy')
hits_geant4, lengths_geant4 = load_all_data('ALL0_no_opticks_event_name/B*/hit.npy')

# Get total number of hits
m_opticks = len(hits_opticks)
m_geant4 = len(hits_geant4)

# Add chi-square calculation function
def calculate_chi2(data1, data2, bins=200):
    """Calculate chi-square between two datasets"""
    hist1, bin_edges = np.histogram(data1, bins=bins)
    hist2, _ = np.histogram(data2, bins=bin_edges)
    ndf = len(bin_edges) - 2  # Degrees of freedom: number of bins - 1
    # Avoid division by zero error
    mask = (hist1 + hist2) > 0
    chi2 = np.sum(((hist1[mask] - hist2[mask]) ** 2) / (hist1[mask] + hist2[mask]))
    return chi2, ndf

# Create three figures: first two remain unchanged, third is new length distribution plot
fig1, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))
fig2, (ax3, ax4, ax5) = plt.subplots(1, 3, figsize=(15, 5))
fig3, ax6 = plt.subplots(1, 1, figsize=(8, 5))

# Process hit time data with logarithmic bins (for display only)
time_min = min(min(hits_opticks[:, 0, 3]), min(hits_geant4[:, 0, 3]))
time_max = max(max(hits_opticks[:, 0, 3]), max(hits_geant4[:, 0, 3]))
log_bins = np.logspace(np.log10(time_min), np.log10(time_max), 50)

# Calculate chi-square for hit time (using linear bins) and plot distribution
chi2_time, ndf_time = calculate_chi2(hits_opticks[:, 0, 3], hits_geant4[:, 0, 3])
chi2ndf_time = chi2_time / ndf_time  # Calculate actual value

ax1.hist(hits_opticks[:, 0, 3], bins=log_bins, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax1.hist(hits_geant4[:, 0, 3], bins=log_bins, alpha=0.7, label='Geant4')
ax1.set_xlabel('Hit Time [ns]')
ax1.set_ylabel('Counts')
ax1.set_xscale('log')
ax1.set_ylim(0, 6.5e5)
ax1.legend(loc='upper right')
ax1.text(0.05, 0.95, f'χ²/ndf = {chi2_time:.1f}/{ndf_time} = {chi2ndf_time:.2f}', 
         transform=ax1.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))
ax1.ticklabel_format(style='sci', axis='y', scilimits=(0,0))

# Calculate chi-square for wavelength
chi2_wave, ndf_wave = calculate_chi2(hits_opticks[:, 2, 3], hits_geant4[:, 2, 3])
chi2ndf_wave = chi2_wave / ndf_wave  # Calculate actual value

# Plot wavelength distribution
ax2.hist(hits_opticks[:, 2, 3], bins=50, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax2.hist(hits_geant4[:, 2, 3], bins=50, alpha=0.7, label='Geant4')
ax2.set_xlabel('Wavelength [nm]')
ax2.set_ylabel('Counts')
ax2.set_ylim(0, 5.2e5)
ax2.legend(loc='upper right')
ax2.text(0.05, 0.95, f'χ²/ndf = {chi2_wave:.1f}/{ndf_wave} = {chi2ndf_wave:.2f}', 
         transform=ax2.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))
ax2.ticklabel_format(style='sci', axis='both', scilimits=(0,0))

fig1.suptitle(f'Comparison of Hit Time and Wavelength results: Opticks({m_opticks} hits) and Geant4({m_geant4} hits)')

# Plot X-coordinate distribution
chi2_x, ndf_x = calculate_chi2(hits_opticks[:, 0, 0], hits_geant4[:, 0, 0])
chi2ndf_x = chi2_x / ndf_x

ax3.hist(hits_opticks[:, 0, 0], bins=50, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax3.hist(hits_geant4[:, 0, 0], bins=50, alpha=0.7, label='Geant4')
ax3.set_xlabel('Global X [mm]')
ax3.set_ylabel('Counts')
ax3.set_ylim(0, 5e4)
ax3.legend(loc='upper right')
ax3.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax3.text(0.05, 0.95, f'χ²/ndf = {chi2_x:.1f}/{ndf_x} = {chi2ndf_x:.2f}', 
         transform=ax3.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))

# Plot Y-coordinate distribution
chi2_y, ndf_y = calculate_chi2(hits_opticks[:, 0, 1], hits_geant4[:, 0, 1])
chi2ndf_y = chi2_y / ndf_y

ax4.hist(hits_opticks[:, 0, 1], bins=50, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax4.hist(hits_geant4[:, 0, 1], bins=50, alpha=0.7, label='Geant4')
ax4.set_xlabel('Global Y [mm]')
ax4.set_ylabel('Counts')
ax4.set_ylim(0, 5e4)
ax4.legend(loc='upper right')
ax4.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax4.text(0.05, 0.95, f'χ²/ndf = {chi2_y:.1f}/{ndf_y} = {chi2ndf_y:.2f}', 
         transform=ax4.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))

# Plot Z-coordinate distribution
chi2_z, ndf_z = calculate_chi2(hits_opticks[:, 0, 2], hits_geant4[:, 0, 2])
chi2ndf_z = chi2_z / ndf_z

ax5.hist(hits_opticks[:, 0, 2], bins=50, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax5.hist(hits_geant4[:, 0, 2], bins=50, alpha=0.7, label='Geant4')
ax5.set_xlabel('Global Z [mm]')
ax5.set_ylabel('Counts')
ax5.set_ylim(0, 5e4)
ax5.legend(loc='upper right')
ax5.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax5.text(0.05, 0.95, f'χ²/ndf = {chi2_z:.1f}/{ndf_z} = {chi2ndf_z:.2f}', 
         transform=ax5.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))

fig2.suptitle(f'Comparison of Global Hit Position: Opticks({m_opticks} hits) and Geant4({m_geant4} hits)')

# Calculate chi-square for hits number and plot distribution
chi2_len, ndf_len = calculate_chi2(lengths_opticks, lengths_geant4)
chi2ndf_len = chi2_len / ndf_len

ax6.hist(lengths_opticks, bins=50, alpha=1.0, histtype='step', linewidth=1.5, label='Opticks')
ax6.hist(lengths_geant4, bins=50, alpha=0.7, label='Geant4')
ax6.set_xlabel('Number of Hits per event')
ax6.set_ylabel('Counts')
ax6.legend(loc='upper right')
ax6.text(0.05, 0.95, f'χ²/ndf = {chi2_len:.1f}/{ndf_len} = {chi2ndf_len:.2f}', 
         transform=ax6.transAxes, verticalalignment='top',
         bbox=dict(facecolor='white', alpha=0.7))
ax6.ticklabel_format(style='sci', axis='both', scilimits=(0,0))

fig3.suptitle(f'Comparison of Hits number: Opticks({m_opticks} hits) and Geant4({m_geant4} hits)')

# Adjust layout
plt.tight_layout()

# Save figures
fig1.savefig('AFGmore_hittime_wavelength_comparison.png', dpi=450, bbox_inches='tight')
fig2.savefig('AFGmore_global_hit_position_comparison.png', dpi=450, bbox_inches='tight')
fig3.savefig('AFGmore_hits_number_comparison.png', dpi=450, bbox_inches='tight')

# Close all figures
plt.close('all')