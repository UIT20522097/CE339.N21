const getTemp = async () => {
  try {
    const url = `https://api.thingspeak.com/channels/2173391/fields/1.json?results=1`;
    //here is how we add a dynamic value (API KEY) to the url
    const res = await fetch(url);
    const data = await res.json();
    return data.feeds;
  } catch (error) {
    console.log("error", error);
  }
};

const renderTemp = async () => {
  document.querySelector("#temp").value = "";

  try {
    const dataTemp = await getTemp();
    const temp = document.getElementById("temp");
    temp.innerHTML = dataTemp[dataTemp.length - 1]?.field1 + "&deg;C";

/*     const date = document.getElementById("date");
    date.innerHTML = new Date(
      Date.parse(dataTemp[dataTemp.length - 1]?.created_at)
    ); */
  } catch (err) {
    console.log("err", err);
  }
};

renderTemp();
setInterval(() => {
  renderTemp();
}, 10000);


const date = document.getElementById("date");

const dateDisplay = async () => {
  date.innerHTML = new Date().toLocaleString('en-US', { timeZone: 'Asia/Ho_Chi_Minh' });
};

setInterval(() => {
  dateDisplay();
}, 1000);

const fanStatus = document.getElementById("fan");
fanStatus.addEventListener("click", handleFan);


async function handleFan() {
  fanStatus.setAttribute('disabled', true);
  setTimeout( async () => {
    fanStatus.removeAttribute('disabled');
  }, 3000);
  const value = fanStatus.checked ? '1' : '0';
  await fetch('/fan', {
    method: 'POST',
    body: value
  })
    .then(response => {
      if (response.ok && response.statusText == 'OK') {
        console.log('Yêu cầu POST thành công');
      } else {
        console.error('Yêu cầu POST thất bại');
      }
    })
    .catch(error => {
      console.error('Lỗi trong quá trình gửi yêu cầu POST', error);
    });
}

const getFanStatus = async () => {
  // Get fan status from server "/fanstatus"
  const res = await fetch('/fanstatus');
  const data = await res.json();
  return data;
}

const renderFanStatus = async () => {
  const temp = await getFanStatus();
  console.log(temp);
  fanStatus.checked = temp;
}

renderFanStatus();
setInterval(() => {
  renderFanStatus();
}, 1000);