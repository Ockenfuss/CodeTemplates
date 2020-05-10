"""Various functions useful when combining python and latex, e.g. when making plots
"""
import numpy as np

def set_size(width='thesis', sitewidth=1, siteheight="golden"):
    #Source: https://jwalton.info/Embed-Publication-Matplotlib-Latex/
    """ Set aesthetic figure dimensions to avoid scaling in latex.

    Parameters
    ----------
    width: float
            Width of the text in latex in pts or a keyword (e.g. 'thesis', 'beamer')
    sitewidth: float
            Fraction of the width which you wish the figure to occupy
    siteheight: float
            Fraction of the sitewidth which you wish the figure to occupy

    Returns
    -------
    fig_dim: tuple
            Dimensions of figure in inches
    """
    #Determine this value with \showthe\textwidth in latex!
    if width == 'thesis':
        width_pt = 469.47049
    elif width == 'beamer':
        width_pt = 307.28987
    else:
        width_pt = width
    # Width of figure
    fig_width_pt = width_pt * sitewidth

    # Convert from pt to inches
    inches_per_pt = 1 / 72.27

    # Golden ratio to set aesthetic figure height
    golden_ratio = (5**.5 - 1) / 2

    # Figure width in inches
    fig_width_in = fig_width_pt * inches_per_pt
    # Figure height in inches
    if siteheight=='golden':
        fig_height_in = fig_width_in * golden_ratio
    else:
        fig_height_in = fig_width_in * siteheight
    fig_dim = (fig_width_in, fig_height_in)

    return fig_dim

def label_panels(ax, position="upper right", color='black'):
    if position=="upper right":
        coords=(0.9,0.9)
    elif position=="upper left":
        coords=(0.1,0.9)
    elif position=="upper middle":
        coords=(0.5,0.9)
    elif position=="lower right":
        coords=(0.9,0.1)
    elif position=="lower left":
        coords=(0.1,0.1)
    elif position=="lower middle":
        coords=(0.5,0.1)
    elif position=="middle left":
        coords=(0.1,0.5)
    elif position=="middle right":
        coords=(0.9,0.5)
    elif position=="center" or position=="middle middle" or position=="middle":
        coords=(0.5,0.5)
    else:
        coords=position
    axf=ax.flatten()
    annotations=[]
    color=np.atleast_1d(color)
    ncolors=len(color)
    for i,a in enumerate(axf):
        letter=chr(97+i)
        annotations.append(a.annotate(letter+")",xy=coords, xycoords='axes fraction', color=color[i%ncolors]))
    return annotations


nice_fonts = {
        # Use LaTeX to write all text
        "text.usetex": True,
        "font.family": "serif",
        # Use 10pt font in plots, to match 10pt font in document
        "axes.labelsize": 10,
        "font.size": 10,
        # Make the legend/label fonts a little smaller
        "legend.fontsize": 8,
        "xtick.labelsize": 8,
        "ytick.labelsize": 8,
        "figure.autolayout": True,
        "pgf.preamble": [
        r"\usepackage{siunitx}"
        ],                                   # or call plt.rcParams["text.latex.preamble"]=[r"\usepackage{siunitx}"] in your script
}
