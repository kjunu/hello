//const fetch = require('node-fetch');
import fetch from "node-fetch";

function sleep(ms) {
	return new Promise((r) => setTimeout(r, ms));
}

const checkCalender = async () => {
	const resp = await fetch("https://booking.ddnayo.com/booking-calendar-api/calendar/accommodation/2642/reservation-calendar?month=202111&calendarTypeCode=RESERVATION_CALENDAR", {
		"headers": {
			"accept": "application/json, text/plain, */*",
			"accept-language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
			"sec-ch-ua": "\"Chromium\";v=\"94\", \"Google Chrome\";v=\"94\", \";Not A Brand\";v=\"99\"",
			"sec-ch-ua-mobile": "?0",
			"sec-ch-ua-platform": "\"macOS\"",
			"sec-fetch-dest": "empty",
			"sec-fetch-mode": "cors",
			"sec-fetch-site": "same-origin",
			"cookie": "SESSION=MWUzYzVjNzQtM2Y3MC00MDhhLWJjMWMtNmY2ODdlODViMmQ3"
		},
		"referrer": "https://booking.ddnayo.com/booking-calendar-status?accommodationId=2642&groupId=",
		"referrerPolicy": "strict-origin-when-cross-origin",
		"body": null,
		"method": "GET",
		"mode": "cors"
	});
	const resp2 = await fetch("https://www.ddnayo.com/RsvSys/?id_hotel=2642", {
  "headers": {
    "accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
    "accept-language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
    "sec-ch-ua": "\"Chromium\";v=\"94\", \"Google Chrome\";v=\"94\", \";Not A Brand\";v=\"99\"",
    "sec-ch-ua-mobile": "?0",
    "sec-ch-ua-platform": "\"macOS\"",
    "sec-fetch-dest": "iframe",
    "sec-fetch-mode": "navigate",
    "sec-fetch-site": "cross-site",
    "upgrade-insecure-requests": "1"
  },
  "referrer": "http://xn--hq1b37ihsn8pgkkas65a.com/",
  "referrerPolicy": "strict-origin-when-cross-origin",
  "body": null,
  "method": "GET",
  "mode": "cors"
});
	//let r = await resp2.json()
	//console.log(r.data.rowDtos[0].columnDtos[6].overDays)
	console.log(resp2)
	return resp2
	//return (r.data.rowDtos[1].columnDtos[6].overDays)
	//fetch("https://booking.ddnayo.com/booking-calendar-api/reservation/accommodation/2642/reservation/rooms/display?baseDate=2021-11-13&stayDays=1&fromHomepage=true", {
	//	"headers": {
	//		"accept": "application/json, text/plain, */*",
	//		"accept-language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
	//		"sec-ch-ua": "\"Chromium\";v=\"94\", \"Google Chrome\";v=\"94\", \";Not A Brand\";v=\"99\"",
	//		"sec-ch-ua-mobile": "?0",
	//		"sec-ch-ua-platform": "\"macOS\"",
	//		"sec-fetch-dest": "empty",
	//		"sec-fetch-mode": "cors",
	//		"sec-fetch-site": "same-origin",
	//		"cookie": "SESSION=MWUzYzVjNzQtM2Y3MC00MDhhLWJjMWMtNmY2ODdlODViMmQ3"
	//	},
	//	"referrer": "https://booking.ddnayo.com/booking-calendar?accommodationId=2642&groupId=",
	//	"referrerPolicy": "strict-origin-when-cross-origin",
	//	"body": null,
	//	"method": "GET",
	//	"mode": "cors"
	//});
	//r = await resp.json()
	//console.log(r)
}
const run = async () => {
	console.log('\u0007');
	while (true) {
		const wait = await checkCalender()
	}
}

run()