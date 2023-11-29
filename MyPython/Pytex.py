"""Various functions useful when combining python and latex, e.g. when making plots
"""
import numpy as np
import subprocess as sp

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
    elif width == 'jgr':
        width_pt = 540.6024
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

def label_panels(ax, position="upper right", color='black', font_weight='normal', startchar='a'):
    """Label panels in a figure with letters

    Parameters
    ----------
    ax : matplotlib.axes.Axes or list of matplotlib.axes.Axes
        Axes to label
    position : str or list of str or list of tuples of float, optional
        Position of the label, either as string or as a list of positions for each panel. In the latter case, positions can be strings or tuples of coordinates. by default "upper right"
    color : str, optional
        The color of the labels, by default 'black'
    font_weight : str, optional
        the font weight of the labels, by default 'normal'
    """
    def _parse_position(position):
        if isinstance(position, str) or isinstance(position, np.str_):
            if position=="upper right" or position=="top right":
                coords=(0.9,0.9)
            elif position=="upper left" or position=="top left":
                coords=(0.1,0.9)
            elif position=="upper middle" or position=="top middle":
                coords=(0.5,0.9)
            elif position=="lower right" or position=="bottom right":
                coords=(0.9,0.1)
            elif position=="lower left" or position=="bottom left":
                coords=(0.1,0.1)
            elif position=="lower middle" or position=="bottom middle":
                coords=(0.5,0.1)
            elif position=="middle left":
                coords=(0.1,0.5)
            elif position=="middle right":
                coords=(0.9,0.5)
            elif position=="center" or position=="middle middle" or position=="middle":
                coords=(0.5,0.5)
        else:
            coords=position
        return coords
    axf=np.array(ax).flatten()
    annotations=[]
    color=np.atleast_1d(color)
    ncolors=len(color)
    if isinstance(position, str):
        position=[position]
    position=[_parse_position(p) for p in position]
    nposition=len(position)
    for i,a in enumerate(axf):
        letter=chr(ord(startchar)+i)
        annotations.append(a.annotate(letter+")",xy=position[i%nposition], xycoords='axes fraction', color=color[i%ncolors], weight=font_weight))
    return annotations

def pdfcrop(pdffile):
    sp.call(f"pdfcrop {pdffile} {pdffile}", shell=True)#Simple execution of string


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

jgr_fonts = {
        # Use LaTeX to write all text
        "text.usetex": True,
        "font.family": "serif",
        "axes.labelsize": 8,
        "font.size": 8,

        "legend.fontsize": 8,
        "xtick.labelsize": 8,
        "ytick.labelsize": 8,
        "figure.autolayout": True,
        # "pgf.preamble": [r"\usepackage{siunitx}"],                                   # or call plt.rcParams["text.latex.preamble"]=[r"\usepackage{siunitx}"] in your script
}
