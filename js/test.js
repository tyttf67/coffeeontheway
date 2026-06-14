let current = 0;
let total = 0;
let answers = [];
let selected = null;



function currentUserId() {
    try {
        const user = JSON.parse(localStorage.getItem("currentUser"));
        if (user && user.id) return Number(user.id);
    } catch (e) {}
    return Number(localStorage.getItem("userId")) || 1;
}

async function requestJson(path, options = {}) {
    const response = await fetch(path, {
        headers: { "Content-Type": "application/json", ...(options.headers || {}) },
        ...options
    });
    const text = await response.text();
    const data = text ? JSON.parse(text) : {};
    if (!response.ok) throw new Error(data.error || `HTTP ${response.status}`);
    return data;
}

function showMessage(msg) {
    const el = document.getElementById("quizMessage");
    if (el) el.textContent = msg;
}

function clearMessage() { showMessage(""); }

// ────────────────────────────────────────
//  Coffee Rain Animation
// ────────────────────────────────────────
function launchCoffeeRain() {
    const rain = document.getElementById("coffeeRain");
    if (!rain) return;
    rain.classList.add("active");

    const images = [
        "img/cb.svg",
        "img/cookies.svg",
        "img/drink1.svg",
        "img/drink2.svg",
        "img/cookies2.svg",
        "img/coffee1.svg"
    ];

    const count = 28;

    for (let i = 0; i < count; i++) {
        setTimeout(() => {
            const drop = document.createElement("img"); // 🔥 ТУТ ГОЛОВНЕ
            drop.className = "coffee-drop";

            drop.src = images[Math.floor(Math.random() * images.length)];

            drop.style.left = Math.random() * 100 + "vw";
            drop.style.width = (18 + Math.random() * 24) + "px"; // замість fontSize
            drop.style.opacity = (0.6 + Math.random() * 0.4).toString();

            const duration = 1.4 + Math.random() * 1.8;
            drop.style.animationDuration = duration + "s";

            rain.appendChild(drop);
            setTimeout(() => drop.remove(), duration * 1000 + 200);
        }, i * 80);
    }

    setTimeout(() => rain.classList.remove("active"), 3500);
}

// ────────────────────────────────────────
//  Init
// ────────────────────────────────────────
async function initQuiz() {
    try {
        const data = await requestJson("/api/quiz/count");
        total = Number(data.count) || 0;
        if (total <= 0) { showMessage("Питання не знайдені."); return; }
        bindNavigation();
        await loadQuestion();
    } catch (error) {
        showMessage(`Помилка підключення: ${error.message}`);
    }
}

async function loadQuestion() {
    clearMessage();
    selected = answers[current] ?? null;
    try {
        const data = await requestJson(`/api/quiz/${current}`);
        renderQuestion(data);
    } catch (error) {
        showMessage(`Не вдалося завантажити питання: ${error.message}`);
    }
}

function renderQuestion(data) {
    const questionEl = document.querySelector(".quiz-question");
    if (questionEl) questionEl.textContent = data.question;

    const progressEl = document.getElementById("progress");
    if (progressEl) progressEl.textContent = `Питання ${current + 1} / ${total}`;

    const wrapper = document.querySelector(".options-wrapper");
    if (!wrapper) return;
    wrapper.innerHTML = "";

    data.options.forEach((option, index) => {
        const row = document.createElement("div");
        row.className = "option-row wave-in";
        row.style.setProperty("--i", index + 1);
        row.setAttribute("role", "radio");
        row.setAttribute("aria-checked", selected === index ? "true" : "false");
        row.innerHTML = `
            <div class="custom-radio"></div>
            <span class="option-text">${option}</span>
        `;

        if (selected === index) {
            highlightRow(row, true);
        }

        row.addEventListener("click", () => {
            selected = index;
            document.querySelectorAll(".option-row").forEach(r => {
                r.setAttribute("aria-checked", "false");
                highlightRow(r, false);
            });
            row.setAttribute("aria-checked", "true");
            highlightRow(row, true);
            clearMessage();
        });

        wrapper.appendChild(row);
    });

    // Back button dim
    const backBtns = document.querySelectorAll(".nav-back");
    backBtns.forEach(btn => {
        btn.style.opacity = current === 0 ? "0.3" : "1";
        btn.style.pointerEvents = current === 0 ? "none" : "auto";
    });
}

function highlightRow(row, active) {
    const radio = row.querySelector(".custom-radio");
    if (!radio) return;
    
    // Перевіряємо, чи активна зараз темна тема
    const isDark = document.documentElement.getAttribute("data-theme") === "dark" || 
                   document.body.getAttribute("data-theme") === "dark";

    if (active) {
        row.classList.add("selected");
        
        if (isDark) {
            // ─── ТЕМНА ТЕМА (КОЛИ НАЖАЛИ) ───
            // Тут міняй кольори як забажаєш:
            radio.style.background = "rgba(119, 64, 64, 0.36)"; // Новий колір радіо кнопки
            radio.style.borderColor = "rgba(238, 162, 162, 0.36)";
            radio.style.boxShadow = "0 0 12px rgba(108, 55, 55, 0.36)";
        } else {
            // ─── СВІТЛА ТЕМА (ТВІЙ ОРИГІНАЛЬНИЙ КОД) ───
            radio.style.background = "rgba(186, 112, 66, 0.95)";
            radio.style.borderColor = "rgba(255, 200, 140, 0.8)";
            radio.style.boxShadow = "0 0 10px rgba(200, 130, 60, 0.7)";
        }
    } else {
        row.classList.remove("selected");
        
        if (isDark) {
            // ─── ТЕМНА ТЕМА (ДЕФОЛТНИЙ СТАН) ───
            radio.style.background = "rgba(88, 39, 39, 0.36)";
            radio.style.borderColor = "rgba(255, 255, 255, 0.18)";
            radio.style.boxShadow = "none";
        } else {
            // ─── СВІТЛА ТЕМА (ТВІЙ ОРИГІНАЛЬНИЙ КОД) ───
            radio.style.background = "rgba(186, 112, 66, 0.25)";
            radio.style.borderColor = "rgba(255, 255, 255, 0.18)";
            radio.style.boxShadow = "none";
        }
    }
}

async function nextQuestion() {
    if (selected === null) { showMessage("Оберіть варіант відповіді."); return; }
    answers[current] = selected;

    const rows = document.querySelectorAll(".option-row");
    rows.forEach(r => { r.classList.remove("wave-in"); r.classList.add("wave-out"); });

    setTimeout(async () => {
        if (current >= total - 1) {
            await finishQuiz();
            return;
        }
        current++;
        await loadQuestion();
    }, 420);
}

async function previousQuestion() {
    if (current === 0) return;
    if (selected !== null) answers[current] = selected;

    const rows = document.querySelectorAll(".option-row");
    rows.forEach(r => { r.classList.remove("wave-in"); r.classList.add("wave-out"); });

    setTimeout(async () => {
        current--;
        await loadQuestion();
    }, 420);
}

async function finishQuiz() {
    const wrapper = document.querySelector('.options-wrapper');
    const questionEl = document.querySelector('.quiz-question');
    const navEl = document.querySelector('.quiz-navigation');

    if (questionEl) questionEl.textContent = 'Майже готово...';
    if (wrapper) wrapper.innerHTML = `
        <div style="display:flex; flex-direction:column; align-items:center; 
                    gap:18px; padding:20px 0; color:#e6dcd5; text-align:center;">
            <div style="font-size:2.5rem;"></div>
            <div style="font-size:1rem; opacity:0.85; line-height:1.6;">
                Підбираємо ідеальну каву...
            </div>
            <div class="loading-dots">
                <span>●</span><span>●</span><span>●</span>
            </div>
        </div>
    `;
    if (navEl) navEl.style.display = 'none';

    try {
        const result = await requestJson("/api/quiz/result", {
            method: "POST",
            body: JSON.stringify({ userId: currentUserId(), answers })
        });
        sessionStorage.setItem("latestCoffeeResult", JSON.stringify(result));
        setTimeout(() => { window.location.href = '/result'; }, 1200);
    } catch (error) {
        showMessage(`Не вдалося зберегти результат: ${error.message}`);
        if (navEl) navEl.style.display = 'flex';
    }
}

function bindNavigation() {
    // Навігаційні кнопки квізу (back / confirm / next)
    const backBtn    = document.querySelector(".nav-back");
    const confirmBtn = document.querySelector(".nav-confirm");
    const nextBtn    = document.querySelector(".nav-next");

    if (backBtn)    backBtn.addEventListener("click", previousQuestion);
    if (confirmBtn) confirmBtn.addEventListener("click", nextQuestion);
    if (nextBtn)    nextBtn.addEventListener("click", nextQuestion);
}

document.addEventListener("DOMContentLoaded", initQuiz);