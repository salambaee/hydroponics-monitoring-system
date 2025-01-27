import { initializeApp } from "https://www.gstatic.com/firebasejs/11.2.0/firebase-app.js";
import { getDatabase, ref, get } from "https://www.gstatic.com/firebasejs/11.2.0/firebase-database.js";
const firebaseConfig = {
  apiKey: "AIzaSyBCpmj7WYHexdh3ERbePm-Wkyz5wwuf8Nc",
  authDomain: "data-sensor-cbfc4.firebaseapp.com",
  databaseURL: "https://data-sensor-cbfc4-default-rtdb.firebaseio.com",
  projectId: "data-sensor-cbfc4",
  storageBucket: "data-sensor-cbfc4.appspot.com",
  messagingSenderId: "1098538542817",
  appId: "1:1098538542817:web:5f286510e7ce85739979a0",
  measurementId: "G-H0EXYBGCM8"
};
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

function updateKelembapan(data) {
  const kelembapanElement = document.getElementById('kelembapan');
  kelembapanElement.textContent = `Humidity : ${data}%`;
}

function updateSuhu(data) {
  const suhuElement = document.getElementById('suhu');
  suhuElement.textContent = `Temperature : ${data} °C`;
}

const kelembapanRef = ref(database, '/sensor/kelembapan');
const suhuRef = ref(database, '/sensor/suhu');

get(kelembapanRef).then((snapshot) => {
  if (snapshot.exists()) {
    const kelembapanData = snapshot.val();
    updateKelembapan(kelembapanData);
  } else {
    console.error("Data kelembapan tidak ditemukan!");
  }
}).catch((error) => {
  console.error("Gagal membaca data kelembapan:", error);
});

// Mendapatkan data suhu
get(suhuRef).then((snapshot) => {
  if (snapshot.exists()) {
    const suhuData = snapshot.val();
    updateSuhu(suhuData);
  } else {
    console.error("Data suhu tidak ditemukan!");
  }
}).catch((error) => {
  console.error("Gagal membaca data suhu:", error);
});
