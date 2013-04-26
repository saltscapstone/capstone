#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Fri Mar 29 14:06:31 2013
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio import window
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.wxgui import fftsink2
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import wx

class top_block(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="Top Block")
		_icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
		self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 150000

		##################################################
		# Blocks
		##################################################
		self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
			self.GetWin(),
			baseband_freq=60000,
			y_per_div=10,
			y_divs=10,
			ref_level=0,
			ref_scale=2.0,
			sample_rate=samp_rate,
			fft_size=1024,
			fft_rate=15,
			average=False,
			avg_alpha=None,
			title="FFT Plot",
			peak_hold=False,
		)
		self.Add(self.wxgui_fftsink2_0.win)
		self.uhd_usrp_source_0 = uhd.usrp_source(
			device_addr="serial=4925e275",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_source_0.set_samp_rate(samp_rate)
		self.uhd_usrp_source_0.set_center_freq(60000, 0)
		self.uhd_usrp_source_0.set_gain(0, 0)
		self.uhd_usrp_source_0.set_bandwidth(10000, 0)
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_c(digital.ofdm_demod(
				options=grc_blks2.options(
					modulation="qpsk",
					fft_length=1024,
					occupied_tones=200,
					cp_length=128,
					snr=10,
					log=None,
					verbose=None,
				),
				callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
			),
		)
		self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, "/home/capstone/output")
		self.blocks_file_sink_0.set_unbuffered(True)

		##################################################
		# Connections
		##################################################
		self.connect((self.uhd_usrp_source_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.blocks_file_sink_0, 0))
		self.connect((self.uhd_usrp_source_0, 0), (self.wxgui_fftsink2_0, 0))


	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)
		self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = top_block()
	tb.Run(True)

