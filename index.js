// Toast function
function toast({ title = "", message = "", type = "info", duration = 2000 }) {
    const main = document.getElementById("toast");
    if (main) {
        const toast = document.createElement("div");

        // Auto remove toast
        const autoRemoveId = setTimeout(function () {
        main.removeChild(toast);
        }, duration + 1000);

        // Remove toast when clicked
        toast.onclick = function (e) {
        if (e.target.closest(".toast__close")) {
            main.removeChild(toast);
            clearTimeout(autoRemoveId);
        }
        };

        const icons = {
        success: "fas fa-check-circle",
        info: "fas fa-info-circle",
        warning: "fas fa-exclamation-circle",
        error: "fas fa-exclamation-circle"
        };
        const icon = icons[type];
        const delay = (duration / 1000).toFixed(2);

        toast.classList.add("toast", `toast--${type}`);
        toast.style.animation = `slideInLeft ease .3s, fadeOut linear 1s ${delay}s forwards`;

        toast.innerHTML = `
                        <div class="toast__icon">
                            <i class="${icon}"></i>
                        </div>
                        <div class="toast__body">
                            <h3 class="toast__title">${title}</h3>
                            <p class="toast__msg">${message}</p>
                        </div>
                        <div class="toast__close">
                            <i class="fas fa-times"></i>
                        </div>
                    `;
        main.appendChild(toast);
    }
    }

    function showToast() {
        toast({
        title: "Xin lỗi!",
        message: "Chức năng này vẫn còn đang xây dựng.",
        });
    }

    //current day, month
    const dayMonth = document.querySelector('.weather__currentday')
    var date = new Date()
    dayMonth.innerHTML = `${date.getDate()} THÁNG ${date.getMonth() + 1} NĂM ${date.getFullYear()}`

    //timing
    let section = document.querySelector("section"),
    icons = document.querySelector(".icons");
    icons.onclick = ()=>{
    section.classList.toggle("dark");
    }
  // creating a function and calling it in every seconds
    setInterval(()=>{
    let date = new Date(),
    hour = date.getHours(),
    min = date.getMinutes(),
    sec = date.getSeconds();
    let d;
    d = hour < 12 ? "AM" : "PM"; //if hour is smaller than 12, than its value will be AM else its value will be pm
    hour = hour > 12 ? hour - 12 : hour; //if hour value is greater than 12 than 12 will subtracted ( by doing this we will get value till 12 not 13,14 or 24 )
    hour = hour == 0 ? hour = 12 : hour; // if hour value is  0 than it value will be 12
    // adding 0 to the front of all the value if they will less than 10
    hour = hour < 10 ? "0" + hour : hour;
    min = min < 10 ? "0" + min : min;
    sec = sec < 10 ? "0" + sec : sec;
    document.querySelector(".hour_num").innerText = hour;
    document.querySelector(".min_num").innerText = min;
    document.querySelector(".sec_num").innerText = sec;
    document.querySelector(".am_pm").innerText = d;
  }, 1000); // 1000 milliseconds = 1s


    //tab ui 
        const $ = document.querySelector.bind(document)
        const $$ = document.querySelectorAll.bind(document)

        const tabs = $$('.page-control')
        const panes = $$('.content')

        tabs.forEach((tab, index) => {
            const pane = panes[index]

            tab.onclick = function() {

            $('.page-control.active').classList.remove('active')
            $('.content.active').classList.remove('active')

            this.classList.add('active')
            pane.classList.add('active')
            }
        })

        //toggle button
        let toggles = document.querySelectorAll('.toggle')
        let toggleBtn = document.querySelectorAll('.toggle-btn')

        toggleBtn.forEach((toggle,index) => {
            toggle.onclick = function() {
                toggles[index].classList.toggle('active')
                if (toggles[0].classList.contains('active')) {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_mode": "ON"
                        })
                }
                else {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_mode": "OFF"
                    })
                }
                if (toggles[1].classList.contains('active')) {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_pump": "ON"
                        })
                }
                else {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_pump": "OFF"
                    })
                }
                if (toggles[2].classList.contains('active')) {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_val": "ON"
                        })
                }
                else {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_val": "OFF"
                    })
                }
                if (toggles[3].classList.contains('active')) {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_feed": "ON"
                        })
                }
                else {
                    firebase.database().ref("/pj2-aqua").update({
                        "sw_feed": "OFF"
                    })
                }
            }
        })

//firebase

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyDMGeNcZ9-bkdgreN6R07BHTa5Iwo58yA4",
    authDomain: "pj2-aquarium.firebaseapp.com",
    databaseURL: "https://pj2-aquarium-default-rtdb.firebaseio.com",
    projectId: "pj2-aquarium",
    storageBucket: "pj2-aquarium.appspot.com",
    messagingSenderId: "622384643282",
    appId: "1:622384643282:web:f8d1471fcb2894b874010b"
};

    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);

//hiển thị nhiet độ, độ đục, mực nước

firebase.database().ref("/pj2-aqua/nhietdo").on("value",function(snapshot){
    const nd = snapshot.val();  
    document.getElementById("nhietdo").innerHTML = nd;
    console.log(nd);
});

firebase.database().ref("/pj2-aqua/doduc").on("value",function(snapshot){
    const dd = snapshot.val();  
    document.getElementById("doduc").innerHTML = dd;
    console.log(dd);
});

firebase.database().ref("/pj2-aqua/mucnuoc").on("value",function(snapshot){
    const mn = snapshot.val();  
    document.getElementById("mucnuoc").innerHTML = mn;
    console.log(mn);
    let tankImg = document.querySelector('#tank-performance')
    if(mn > 10 && mn < 14) {
        tankImg.src = './assets/img/WaterTankRed.png'
    } else if ( mn >= 6 && mn <= 10) {
        tankImg.src = './assets/img/WaterTank.png'
    } else if ( mn > 1 && mn < 6) {
        tankImg.src = './assets/img/WaterTankYellow.png'
    } else if ( mn <= 1) {
        tankImg.src = './assets/img/WaterTankEmpty.png'
    } else if ( mn >= 14) {
        tankImg.src = './assets/img/WaterTankFull.png'
    }
});

 // Hàm gửi dữ liệu lên Firebase
function sendToFirebase() {
    var timeInput = document.getElementById("timeInput").value;

    // Kiểm tra định dạng thời gian
    var regex = /^([0-1]?[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$/;
    if (!regex.test(timeInput)) {
        alert("Định dạng thời gian không hợp lệ! Vui lòng nhập lại theo định dạng h:mm:ss");
        return;
    }

    // Gửi dữ liệu lên Firebase Realtime Database
    var firebaseRef = firebase.database().ref('/pj2-aqua');
    firebaseRef.child('timer').set(timeInput).then(function() {
    alert("cài đặt thời gian cho cá ăn thành công!");
    }).catch(function(error) {
    alert("Đã xảy ra lỗi: " + error.message);
    });
}

//Update Bulb status-----when reload website-------
firebase.database().ref("/pj2-aqua").get().then((snapshot) => {
    if(snapshot.exists()){
    console.log(snapshot.val())

    let status = snapshot.val()
    if (status["sw_mode"] == "ON")
        {
            toggles[0].classList.add('active')
        }
    else
        {
            toggles[0].classList.remove('active')
        }
    
    if (status["sw_pump"] == "ON")
        {
            toggles[1].classList.add('active')
        }
    else
        {
            toggles[1].classList.remove('active')
        }

    if (status["sw_val"] == "ON")
        {
            toggles[2].classList.add('active')
        }
    else
        {
            toggles[2].classList.remove('active')
        }

    if (status["sw_feed"] == "ON")
        {
            toggles[3].classList.add('active')
        }
    else
        {
            toggles[3].classList.remove('active')
        }
    }
    else
    console.log("No data available!")
})

