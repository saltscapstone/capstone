#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Fri Mar 29 14:07:45 2013
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser

class top_block(gr.top_block):

	def __init__(self):
		gr.top_block.__init__(self, "Top Block")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 150000

		##################################################
		# Blocks
		##################################################
		self.uhd_usrp_sink_0 = uhd.usrp_sink(
			device_addr="serial=4a54d7c8",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
		self.uhd_usrp_sink_0.set_center_freq(60000, 0)
		self.uhd_usrp_sink_0.set_gain(0, 0)
		self.uhd_usrp_sink_0.set_bandwidth(10000, 0)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_f(digital.ofdm_mod(
				options=grc_blks2.options(
					modulation="qpsk",
					fft_length=1024,
					occupied_tones=200,
					cp_length=128,
					pad_for_usrp=True,
					log=None,
					verbose=None,
				),
			),
			payload_length=0,
		)
		self.blocks_file_source_0 = blocks.file_source(gr.sizeof_float*1, "/home/ubuntu/input", False)

		##################################################
		# Connections
		##################################################
		self.connect((self.digital_ofdm_mod_0, 0), (self.uhd_usrp_sink_0, 0))
		self.connect((self.blocks_file_source_0, 0), (self.digital_ofdm_mod_0, 0))


	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = top_block()
	tb.start()
	raw_input('Press Enter to quit: ')
	tb.stop()

