//const _url = "google.com";
//const _url = "https://r.camperstory.com/resMain.hbb?reserve_path=RP&campseq=1620#20211024^20211025^1";
const _url = "https://r.camperstory.com/resMain.hbb?reserve_path=RP&campseq=1620#20211029^20211031^2";
const webdriver = require('selenium-webdriver');

const {By,Util, Key} = webdriver;

require('chromedriver');

const driver = new webdriver.Builder().forBrowser('chrome').build();

function sleep(ms) {
  return new Promise((r) => setTimeout(r, ms));
}

async function waitFor(xpath, time=10) {
	//const cond = webdriver.until.elementLocated({ xpath: xpath });
	//await driver.wait(cond, 1000, 'find', xpath);
	await sleep(time)
	return driver.findElement(By.xpath(xpath))
}
async function waitForUntil(xpath, time=1000) {
	const cond = webdriver.until.elementLocated({ xpath: xpath });
	await driver.wait(cond, time, 'find');
	return driver.findElement(By.xpath(xpath))
}
const now = new Date()
//driver.get(_url);
const millisTill = new Date(now.getFullYear(), now.getMonth(), now.getDate(), 14, 58, 0, 0) - now;
setTimeout(
(async () => {
	let name = "test"
	let car_no = "1234"
	let p1 = "1123"
	let p2 = "3333"
	while(1){
	console.log(process.argv);
	name = process.argv[2]
	car_no = process.argv[3]
	p1 = process.argv[4]
	p2 = process.argv[5]
	console.log(name, car_no, p1, p2);
	try {
		console.log(new Date());
		driver.get(_url);
		//await driver.navigate().refresh();
		console.log('step1', new Date());
		await (await waitForUntil("//*[@id=\"form\"]/div[3]/div[2]/div/div/div[1]/span")).click();
		console.log('step2', new Date());
		await (await waitFor("//*[@id=\"campsiteseq_10796\"]/div")).click();
		console.log('step3', new Date());
		await driver.findElement(By.xpath("//*[@id=\"container\"]/div/div[2]/div[3]/div/button")).click();
		console.log('step4', new Date());
		await driver.findElement(By.xpath("//*[@id=\"name\"]")).sendKeys(name);
		console.log('step5', new Date());
		await driver.findElement(By.xpath("//*[@id=\"h_telno2\"]")).sendKeys(p1);
		console.log('step6', new Date());
		await driver.findElement(By.xpath("//*[@id=\"h_telno3\"]")).sendKeys(p2);
		console.log('step7', new Date());
		await driver.findElement(By.xpath("//*[@id=\"car_no\"]")).sendKeys(car_no);
		console.log('step8 select cash', new Date());
		await (await waitFor("//*[@id=\"SelCashGb\"]")).click();
		await driver.findElement(By.xpath("//*[@id=\"SelCashGb\"]/option[2]")).click();
		console.log('step9 add receipt', new Date());
		await (await waitFor("//*[@id=\"container\"]/div/div[2]/div[5]/ul/li[1]/label")).click();
		console.log('step10 agree', new Date());
		await (await waitFor("//*[@id=\"div_agree1\"]/label/span[1]")).click();
		console.log('step10.1 agree', new Date());
		await (await waitFor("//*[@id=\"div_agree2\"]/label/span[1]")).click();
		console.log('step10.2 agree', new Date());
		await (await waitFor("//*[@id=\"div_agree3\"]/label/span[1]")).click();

		console.log('step9.1', new Date());
		await (await waitFor("//*[@id=\"divVBank\"]/div[2]/div[2]/ul/li[1]/label/span[1]")).click();
		//*[@id="div_agree1"]/label/span[2]
		//await driver.findElement(By.xpath("//*[@id=\"div_agree1\"]/label/span[1]")).click();
		//await driver.findElement(By.xpath("//*[@id=\"div_agree2\"]/label/span[1]")).click();
		//await driver.findElement(By.xpath("//*[@id=\"div_agree3\"]/label/span[1]")).click();
		//console.log('step11', new Date());
		await driver.findElement(By.xpath("//*[@id=\"pc_btn\"]")).click();
		await driver.wait(webdriver.until.alertIsPresent());
		await (await driver.switchTo().alert()).accept();
	} catch (e) {
		console.log(e)
		console.log('continue')
		continue
	} finally {
		console.log('finally');
		await driver.sleep(1200);
		//await driver.quit();
	}
	}
}), millisTill);

