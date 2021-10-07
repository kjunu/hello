package cmd

import (
	"fmt"

	"github.com/fedesog/webdriver"
	"github.com/spf13/cobra"
)

func init() {
	webCmd.AddCommand(driverCmd)
	rootCmd.AddCommand(webCmd)
}

var webCmd = &cobra.Command{
	Use:   "web",
	Short: "web",
	Long:  `web commands`,
}
var driverCmd = &cobra.Command{
	Use:   "driver",
	Short: "driver",
	Long:  `chrome web driver`,
	RunE:  driver,
}

var (
	//path = "/Users/jaden/work/sv/node_modules/.bin/chromedriver"
	path = "/Users/jaden/Downloads/chromedriver94"
	url  = "https://chromedriver.storage.googleapis.com/index.html?path=94.0.4606.61/"
)

func driver(cmd *cobra.Command, args []string) error {
	chromeDriver := webdriver.NewChromeDriver(path)
	err := chromeDriver.Start()
	defer chromeDriver.Stop()
	if err != nil {
		return err
	}
	desired := webdriver.Capabilities{"Platfrom": "Linux"}
	required := webdriver.Capabilities{}
	session, err := chromeDriver.NewSession(desired, required)
	defer session.Delete()
	if err != nil {
		return err
	}
	session.Url(url)
	fmt.Println(session)
	return nil
}
