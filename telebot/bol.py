import pandas as pd
#import matplotlib.pyplot as plt

class Bollinger:
	WINDOW = 20
	def plot_stock_data(self, df):
		return df['Close'].plot(title='Bitcoin Bollinger Bands', label='BTC')

	# compute rolling mean with 20 day window
	def plot_rolling_mean(self, df, ax):
		#rm_BTC = pd.rolling_mean(df['Close'], window=self.WINDOW)
		rm_BTC = pd.Series(df['Close']).rolling(window=self.WINDOW,center=False).mean()
		rm_BTC.plot(label='Rolling Mean', ax=ax)
		return rm_BTC
	
	def add_plot_labels(self, ax):
		ax.set_xlabel('Date')
		ax.set_ylabel('Price')
		ax.legend(loc='upper left')
	
	def plot_bollinger_bands(self, rm_BTC, df, ax):
		#rstd_BTC = pd.rolling_std(df['Close'], window=self.WINDOW)
		rstd_BTC = pd.Series(df['Close']).rolling(window=self.WINDOW,center=False).std()
		upper_band = rm_BTC + (2 * rstd_BTC)
		lower_band = rm_BTC - (2 * rstd_BTC)
		upper_band.plot(label='upper band', ax=ax)
		lower_band.plot(label='lower band', ax=ax)
		return upper_band, lower_band
	
	def bollinger(self, df):
		ax = self.plot_stock_data(df)
		rm_BTC = self.plot_rolling_mean(df, ax)
		return self.plot_bollinger_bands(rm_BTC, df, ax)
		#self.add_plot_labels(ax)
		#plt.show()
	
## read in CSV from file
#def get_stock_data():
#	prices = pd.read_csv('./bitstampusd.csv', index_col='Date',parse_dates=True,
#						usecols=['Date', 'Close'], na_values=['nan'])
#	dates = pd.date_range('2016-06-22', '2017-06-22')
#	df = pd.DataFrame(index=dates)
#	df = df.join(prices)
#	df = df.dropna()
#	print(df)
#	return df
#
#
#
## main function
#
#if __name__ == '__main__':
#	Bollinger().bollinger(get_stock_data())