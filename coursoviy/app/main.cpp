#define _WIN32_WINNT 0x0601

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm> // Для std::min

#include "coffee.h"
#include "consoleApp.h"
#include "myTest.h"
#include "storage.h"
#include "coffeeCatalog.h"
#include "crow_all.h"
#include "coffeeSelector.h"

namespace {

    // ─────────────────────────────────────────────
    //  Читання файлу з диску
    // ─────────────────────────────────────────────
    std::string readTextFile(const char* fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) return "";
        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    // ─────────────────────────────────────────────
    //  Fallback-вміст головної сторінки з модальним вікном верифікації
    // ─────────────────────────────────────────────
    // ─────────────────────────────────────────────
    //  Fallback-вміст головної сторінки з модальним вікном верифікації
    // ─────────────────────────────────────────────
    std::string defaultIndexHtml() {
        return R"(<!DOCTYPE html>
<html lang="uk">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Coffee On The Way - Головна</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <main class="page">
        <header class="topbar">
            <div class="nav-group">
                <button class="catalog-btn" onclick="window.location.href='/meals'">Меню</button>
            </div>
            <h1 class="logo">coffee on the way</h1>
            <div class="nav-group nav-right">
                <div class="theme-toggle">
                    <div class="toggle-icon active">☀️</div>
                </div>
            </div>
        </header>

        <section class="hero">
            <p>Твій ідеальний кавовий путівник.</p>
            <button class="test-btn" id="startTestBtn" type="button">☕ Почати тест</button>
        </section>

        <section class="section auth-section">
            <div class="text-block">
                <h2>Приєднуйся до кавового клубу</h2>
                <p>Авторизуйся або створи новий акаунт, щоб відстежувати свою кавову статистику.</p>
                
                <div class="auth-container" id="authPanel">
                    <form id="registerForm" class="auth-form">
                        <h3>Реєстрація</h3>
                        <input id="registerLogin" placeholder="Логін" required>
                        <input id="registerPassword" type="password" placeholder="Пароль" required>
                        <button type="submit" class="form-submit-btn">Створити акаунт ✨</button>
                    </form>

                    <form id="loginForm" class="auth-form">
                        <h3>Вхід</h3>
                        <input id="loginLogin" placeholder="Логін" required>
                        <input id="loginPassword" type="password" placeholder="Пароль" required>
                        <button type="submit" class="form-submit-btn">Увійти ☕</button>
                    </form>
                </div>

                <div id="profilePanel" class="profile-card" style="display:none;">
                    <h3>Вітаємо, <span id="currentUser">Гість</span>!</h3>
                    <p>Твій кавовий профіль активовано.</p>
                    <button id="logoutBtn" class="logout-btn" type="button">Вийти з профілю</button>
                </div>
            </div>

            <div class="photo-stack">
                <div class="round-btn">☕</div>
                <div class="round-btn">🌱</div>
            </div>
        </section>

        <footer style="margin-top: 50px;">
            <div class="actions" style="display:flex; gap:10px; justify-content:center; margin-bottom:20px;">
                <button id="refreshStatsBtn" style="background:rgba(255,255,255,0.05); color:#fff; border:1px solid rgba(255,255,255,0.1); padding:8px 16px; border-radius:12px; cursor:pointer;">Оновити статистику</button>
                <button id="testServerBtn" style="background:rgba(255,255,255,0.05); color:#fff; border:1px solid rgba(255,255,255,0.1); padding:8px 16px; border-radius:12px; cursor:pointer;">Перевірити сервер</button>
                <button id="saveDataBtn" style="background:rgba(255,255,255,0.05); color:#fff; border:1px solid rgba(255,255,255,0.1); padding:8px 16px; border-radius:12px; cursor:pointer;">Зберегти дані</button>
            </div>
            <p id="message" style="opacity:0.6;">Сервер працює стабільно.</p>
        </footer>
    </main>

    <div class="modal-overlay" id="authModal">
        <div class="modal-card">
            <h3>Потрібна верифікація 🧭</h3>
            <p>Щоб зафіксувати твої відповіді та зберегти підібрану каву в системі, потрібно авторизуватись або увійти у свій акаунт.</p>
            <div class="modal-btn-group">
                <button class="modal-btn primary" onclick="document.getElementById('registerLogin').focus(); document.getElementById('authModal').classList.remove('active');">Зареєструватися на сторінці</button>
                <button class="modal-btn primary" onclick="document.getElementById('loginLogin').focus(); document.getElementById('authModal').classList.remove('active');">Вже є акаунт? Увійти</button>
                <button class="modal-btn secondary" id="closeModalBtn">Скасувати</button>
            </div>
        </div>
    </div>

    <script>
        document.addEventListener("DOMContentLoaded", () => {
            const startTestBtn = document.getElementById("startTestBtn");
            const authModal = document.getElementById("authModal");
            const closeModalBtn = document.getElementById("closeModalBtn");

            if (startTestBtn) {
                startTestBtn.addEventListener("click", (e) => {
                    e.preventDefault();
                    const userRaw = localStorage.getItem("currentUser");
                    if (userRaw) {
                        window.location.href = "/test";
                    } else {
                        authModal.classList.add("active");
                    }
                });
            }

            if (closeModalBtn) {
                closeModalBtn.addEventListener("click", () => {
                    authModal.classList.remove("active");
                });
            }
        });
    </script>
    <script src="/script.js"></script>
</body>
</html>)";
    }
    std::string defaultCss() {
        return R"(* {
  box-sizing: border-box;
}

html,
body {
  margin: 0;
  min-height: 100%;
  zoom: 1.15;
  background: linear-gradient(180deg, #110701 100%, #2a1406 100%);
  color: #ffffff;
  font-family: "Roboto Serif", Georgia, serif;
}

.page {
  width: 100%;
  max-width: 1120px;
  margin: 0 auto;
  min-height: 100vh;
  padding: 16px 16px 0;
  background:
    radial-gradient(circle at 50% 34%, rgba(72, 43, 8, 0.58), transparent 32%),
    linear-gradient(180deg, #110701 0%, #2a1406 100%);
}

.topbar {
  min-height: 76px;
  display: grid;
  grid-template-columns: minmax(190px, 1fr) auto minmax(190px, 1fr);
  align-items: start;
}

.nav-group {
  display: flex;
  align-items: center;
  gap: 8px;
}

.nav-right {
  justify-content: flex-end;
}

.catalog-btn,
.round-btn,
.theme-toggle,
.test-btn {
  background: rgba(225, 219, 202, 0.2);
  backdrop-filter: blur(18px) saturate(130%);
  -webkit-backdrop-filter: blur(18px) saturate(130%);
  border: 1px solid rgba(255, 255, 255, 0.18);
  box-shadow:
    inset 0 1px 2px rgba(255,255,255,0.18),
    inset 0 -2px 5px rgba(0,0,0,0.25),
    0 6px 16px rgba(0,0,0,0.45);
  position: relative;
  overflow: hidden;
}

.catalog-btn::before,
.round-btn::before,
.theme-toggle::before,
.test-btn::before {
  content: "";
  position: absolute;
  inset: 0;
  border-radius: inherit;
  background: linear-gradient(
    -45deg,
    rgba(255,255,255,0.25) 0%,
    rgba(255,255,255,0.05) 40%,
    rgba(0,0,0,0.15) 100%
  );
  opacity: 0.6;
  pointer-events: none;
}

.catalog-btn {
  width: 78px;
  height: 27px;
  border-radius: 18px;
  color: #ffffff;
  font-family: "Roboto", Arial, sans-serif;
  font-size: 12px;
  cursor: pointer;
}

.round-btn {
  width: 30px;
  height: 28px;
  border-radius: 50%;
  display: grid;
  place-items: center;
  padding: 0;
}

.round-btn img {
  width: 12px;
  height: 12px;
  object-fit: contain;
  display: block;
}

.profile-btn img {
  width: 12px;
  height: 12px;
}

.theme-toggle {
  width: 70px;
  height: 27px;
  border-radius: 18px;
  display: flex;
  align-items: center;
  gap: 18px;
  padding: 6px;
  cursor: pointer;
}

.toggle-icon {
  width: 21px;
  height: 21px;
  border-radius: 50%;
  display: grid;
  place-items: center;
}

.toggle-icon.active {
  height: 26px;
  width: 26px;
  margin-left: -2px;
}

.toggle-icon.active img {
  padding-top: 2px;
  width: 32px;
  height: 30px;
  object-fit: contain;
}

.toggle-icon img {
  padding-top: 4px;
  padding-right: 6px;
  width: 18px;
  height: 18px;
}

.logo {
  margin: 18px 0 0;
  font-family: "Rubik Bubbles", system-ui;
  font-size: 23px;
  font-weight: 400;
  color: #e1dbca;
  transform: rotate(-10deg) skewX(-9deg);
  text-shadow: 4px 4px 4px rgba(0, 0, 0, 0.25);
  white-space: nowrap;
}

.hero {
  margin-top: 70px;
  margin-left: 52px;
  width: 270px;
}

.hero p {
  margin: 0;
  font-size: 17px;
  line-height: 1.15;
  letter-spacing: 0.34px;
}

.test-btn {
  margin-top: 32px;
  width: 112px;
  height: 32px;
  border-radius: 32px;
  background: #ffffff;
  color: #000000;
  font-family: Roboto, Arial, sans-serif;
  font-size: 12px;
  box-shadow: 2px 2px 10px #ffffff, inset 0 4px 4px rgba(0, 0, 0, 0.25);
  cursor: pointer;
  transition: all 0.2s ease-in-out;
}

.test-btn:hover {
  background: #6d5959;
  transform: translateY(-2px);
  box-shadow: 0 5px 15px rgba(255, 255, 255, 0.4);
}

.test-btn:active {
  transform: translateY(0);
}

.section {
  width: min(850px, 100%);
  margin: 148px auto 0;
  display: grid;
  grid-template-columns: minmax(0, 1fr) 118px;
  gap: 46px;
  align-items: start;
}

.types-section {
  margin-top: 82px;
}

.text-block h2 {
  margin: 0 0 28px;
  font-size: 25px;
  font-weight: 400;
  letter-spacing: 0.5px;
}

.text-block p {
  margin: 0 0 24px;
  font-size: 12px;
  line-height: 1.3;
  letter-spacing: 0.2px;
  opacity: 0.8;
}

.photo-stack {
  display: flex;
  flex-direction: column;
  gap: 20px;
}

.photo-stack img {
  width: 118px;
  height: 118px;
  object-fit: cover;
  border-radius: 12px;
  box-shadow: 4px 4px 16px rgba(255, 255, 255, 0.48);
}

.types-section .photo-stack img {
  height: 190px;
}

footer {
  margin-top: 68px;
  padding: 28px 0 24px;
  text-align: center;
  color: #ffffff;
  font-size: 10px;
}

/* ── СТИЛІ ДЛЯ ФОРМ АВТОРИЗАЦІЇ/РЕЄСТРАЦІЇ (Нові) ── */
.auth-container {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
  gap: 20px;
  margin-top: 25px;
}

.auth-form {
  background: rgba(19, 7, 4, 0.6);
  border: 1px solid rgba(255, 255, 255, 0.05);
  padding: 20px;
  border-radius: 20px;
  display: flex;
  flex-direction: column;
  gap: 12px;
  box-shadow: 0 10px 30px rgba(0,0,0,0.4);
}

.auth-form h3 {
  margin: 0 0 5px 0;
  font-size: 1.1rem;
  color: #e1dbca;
}

.auth-form input {
  height: 38px;
  border-radius: 10px;
  border: 1px solid rgba(255, 255, 255, 0.1);
  background: #080201;
  color: #fff;
  padding: 0 12px;
  font-size: 0.9rem;
}

.auth-form input:focus {
  outline: none;
  border-color: #8b5e3c;
}

.form-submit-btn {
  height: 38px;
  border-radius: 10px;
  border: none;
  background: #8b5e3c;
  color: #fff;
  font-weight: bold;
  cursor: pointer;
  transition: background 0.2s;
}

.form-submit-btn:hover {
  background: #a06e4c;
}

.profile-card {
  background: rgba(139, 94, 60, 0.15);
  border: 1px solid rgba(139, 94, 60, 0.3);
  padding: 20px;
  border-radius: 20px;
  text-align: center;
}

.logout-btn {
  padding: 8px 16px;
  background: #cc3333;
  color: white;
  border: none;
  border-radius: 10px;
  cursor: pointer;
}

/* ── ФІКСАЦІЯ МОДАЛЬНОГО ВІКНА СУВОРO ПО ЦЕНТРУ ── */
.modal-overlay {
  position: fixed;
  top: 0; left: 0;
  width: 100vw; height: 100vh;
  background: rgba(10, 3, 1, 0.88);
  backdrop-filter: blur(12px);
  -webkit-backdrop-filter: blur(12px);
  z-index: 99999;
  display: none;
  justify-content: center;
  align-items: center;
  transition: opacity 0.3s ease;
  opacity: 0;
  pointer-events: none;
}

.modal-overlay.active {
  display: flex;
  opacity: 1;
  pointer-events: auto;
}

.modal-card {
  background: #130704 !important;
  border: 1px solid rgba(255, 255, 255, 0.08) !important;
  padding: 40px 30px !important;
  border-radius: 32px !important;
  max-width: 400px !important;
  width: 90% !important;
  text-align: center !important;
  box-shadow: 0 25px 60px rgba(0,0,0,0.8) !important;
}

.modal-card h3 {
  color: #e3d5ca !important;
  margin-top: 0;
  margin-bottom: 15px !important;
  font-size: 1.4rem !important;
}

.modal-card p {
  color: rgba(230, 220, 213, 0.7) !important;
  font-size: 0.95rem !important;
  margin-bottom: 25px !important;
  line-height: 1.5 !important;
}

/* Твої кастомні стилі для кнопок модалки */
.modal-btn {
  padding: 14px;
  border-radius: 20px;
  font-family: 'Comfortaa', sans-serif;
  font-size: 0.95rem;
  cursor: pointer;
  transition: all 0.2s ease;
  width: 100%;
}

.modal-btn.primary {
  background: #8b5e3c;
  border: 1px solid #704a2e;
  color: #ffffff;
}

.modal-btn.primary:hover {
  background: #a06e4c;
  box-shadow: 0 4px 12px rgba(139, 94, 60, 0.3);
}

.modal-btn.secondary {
  background: transparent;
  border: none;
  color: rgba(230, 220, 213, 0.5);
  font-size: 0.85rem;
}

.modal-btn.secondary:hover {
  color: #ffffff;
  background: rgba(255, 255, 255, 0.05);
}

/* Адаптивність */
@media (max-width: 760px) {
  .page { padding: 24px 16px 0; }
  .topbar { grid-template-columns: 1fr; gap: 16px; }
  .nav-right { justify-content: flex-start; }
  .logo { justify-self: center; }
  .hero { margin-left: 0; }
  .section { grid-template-columns: 1fr; margin-top: 90px; }
  .photo-stack { display: grid; grid-template-columns: repeat(2, 118px); justify-content: center; }
}

/* 🌙 ТЕМНА ТЕМА */
[data-theme="dark"] { color: #f5f5f5; }
[data-theme="dark"] .quiz-card { background: rgba(20,20,20,0.9); }
[data-theme="dark"] .option-row { background: rgba(255,255,255,0.05); }
[data-theme="dark"] .option-text { color: #eee; }
[data-theme="dark"] .theme-toggle { background: rgba(255, 255, 255, 0.1); }
[data-theme="dark"] .toggle-icon { opacity: 0.5; }
[data-theme="dark"] .toggle-icon.active { opacity: 1; transform: scale(1.1); }
[data-theme="dark"] .toggle-icon.active img { filter: drop-shadow(0 0 4px rgba(255,255,255,0.6)); }
)";
    }

    std::string defaultTestHtml() {
        return R"(<!DOCTYPE html>
<html lang="uk">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Coffee On The Way - Quiz</title>
    <link href="https://fonts.googleapis.com/css2?family=Comfortaa:wght@400;700&family=Montserrat:ital,wght@1,900&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="/test.css">
</head>
<body>
    <header class="top-header">
        <div class="pill-badge status-badge">
            <span class="bean-icon">🧭</span>
            <span class="divider">|</span>
            <span class="bean-icon">🧭</span>
        </div>
        <div class="pill-badge profile-badge">
            <span class="profile-icon">👤</span>
        </div>
    </header>
    <main class="quiz-container">
        <h1 class="brand-logo">coffee on the way</h1>
        <div class="quiz-card">
            <h2 class="quiz-question">Чи полюбляєте vi молоко?</h2>
            <div class="options-wrapper">
                <div class="option-row" style="--i:1"><span class="option-text">Звичайно</span><div class="custom-radio"></div></div>
                <div class="option-row" style="--i:2"><span class="option-text">Не люблю</span><div class="custom-radio"></div></div>
                <div class="option-row" style="--i:3"><span class="option-text">Іноді</span><div class="custom-radio"></div></div>
            </div>
            <div class="quiz-navigation">
                <button class="nav-circle-btn">&lt;</button>
                <button class="nav-circle-btn accept-btn">✓</button>
                <button class="nav-circle-btn">&gt;</button>
            </div>
        </div>
    </main>
    <script src="/test.js"></script>
</body>
</html>)";
    }

    std::string defaultTestCss() {
        return R"(*{box-sizing:border-box;margin:0;padding:0}
body{min-height:100vh;background:radial-gradient(circle at center,#36190e 0%,#120602 100%);font-family:'Comfortaa',sans-serif;display:flex;justify-content:center;align-items:center;overflow:hidden;position:relative}
.top-header{position:absolute;top:30px;right:40px;display:flex;gap:15px;align-items:center}
.pill-badge{background:rgba(255,255,255,.04);border:1px solid rgba(255,255,255,.08);backdrop-filter:blur(5px);border-radius:100px;display:flex;align-items:center;justify-content:center;padding:8px 16px;height:40px}
.status-badge{gap:10px}.divider{color:rgba(255,255,255,.15);font-size:.8rem}.profile-badge{width:40px;padding:0}
.quiz-container{display:flex;flex-direction:column;align-items:center;width:100%;max-width:460px;padding:20px}
.brand-logo{font-family:'Montserrat',sans-serif;font-weight:900;font-style:italic;font-size:2.2rem;color:#e3d5ca;text-transform:lowercase;transform:rotate(-6deg);margin-bottom:45px;letter-spacing:-.5px;text-shadow:0 4px 15px rgba(0,0,0,.4)}
.quiz-card{background:#130704;width:100%;border-radius:36px;padding:45px 35px 35px;border:1px solid rgba(255,255,255,.03);box-shadow:0 25px 60px rgba(0,0,0,.65),inset 0 0 25px rgba(139,94,60,.08);text-align:center}
.quiz-question{font-size:1.15rem;font-weight:400;color:#f7ebe1;margin-bottom:35px;letter-spacing:.5px}
.options-wrapper{display:flex;flex-direction:column;gap:16px;margin-bottom:35px}
.option-row{background:rgba(10,3,1,.7);border:1px solid rgba(255,255,255,.04);border-radius:24px;padding:18px 24px;display:flex;justify-content:space-between;align-items:center;cursor:pointer;transition:all .25s ease;opacity:0;transform:translateY(35px)}
.option-row:hover{background:rgba(255,255,255,.02);border-color:rgba(255,255,255,.08)}
.option-text{color:#e6dcd5;font-size:.95rem}
.custom-radio{width:22px;height:22px;border-radius:50%;background:#080201;box-shadow:inset 0 2px 5px rgba(0,0,0,.8);border:1px solid rgba(255,255,255,.03)}
.option-row.wave-in{animation:waveIn .65s cubic-bezier(.25,1,.5,1) forwards;animation-delay:calc(var(--i)*.12s)}
.option-row.wave-out{animation:waveOut .45s cubic-bezier(.25,1,.5,1) forwards;animation-delay:calc(var(--i)*.08s)}
.quiz-navigation{display:flex;justify-content:center;gap:16px;align-items:center}
.nav-circle-btn{width:44px;height:44px;border-radius:50%;background:transparent;border:1px solid rgba(255,255,255,.1);color:#e6dcd5;font-size:1rem;cursor:pointer;display:flex;align-items:center;justify-content:center;transition:all .2s ease}
.nav-circle-btn:hover{background:rgba(255,255,255,.05);border-color:rgba(255,255,255,.2)}
.accept-btn{font-size:1.1rem}
@keyframes waveIn{0%{opacity:0;transform:translateY(40px)}100%{opacity:1;transform:translateY(0)}}
@keyframes waveOut{0%{opacity:1;transform:translateY(0)}100%{opacity:0;transform:translateY(40px)}})";
    }

    std::string defaultTestJs() {
        return R"(
let currentQuestionIndex = 0;
let totalQuestions = 0;
let selectedAnswers = []; // Тут зберігаємо індекси вибраних відповідей (0, 1 або 2)
let currentSelectedOption = null; // Поточна обрана опція на поточному кроці

document.addEventListener("DOMContentLoaded", () => {
    // 1. Спочатку дізнаємося кількість питань на бекенді
    fetch('/api/quiz/count')
        .then(res => res.json())
        .then(data => {
            totalQuestions = data.count;
            if (totalQuestions > 0) {
                loadQuestion(currentQuestionIndex);
            }
        })
        .catch(err => console.error("Помилка завантаження кількості питань:", err));

    // 2. Налаштовуємо кнопки навігації
    const navButtons = document.querySelectorAll('.nav-circle-btn');
    
    // Кнопка НАЗАД (<) - зазвичай перша
    navButtons[0].addEventListener('click', () => {
        if (currentQuestionIndex > 0) {
            saveCurrentAnswer();
            currentQuestionIndex--;
            animateWaveOut(() => loadQuestion(currentQuestionIndex));
        }
    });

    // Кнопка ПІДТВЕРДИТИ (✓) - друга (accept-btn)
    document.querySelector('.accept-btn').addEventListener('click', () => {
        if (currentSelectedOption === null) {
            alert("Будь ласка, оберіть варіант відповіді!");
            return;
        }
        saveCurrentAnswer();
        
        // Якщо це було останнє питання — відправляємо на розрахунок кави
        if (selectedAnswers.length === totalQuestions) {
            sendAnswersToBackend();
        } else {
            alert("Ви відповіли не на всі питання!");
        }
    });

    // Кнопка ВПЕРЕД (>) - третя
    navButtons[2].addEventListener('click', () => {
        if (currentSelectedOption === null) {
            alert("Будь ласка, оберіть варіант відповіді перед переходом далі!");
            return;
        }
        saveCurrentAnswer();
        
        if (currentQuestionIndex < totalQuestions - 1) {
            currentQuestionIndex++;
            animateWaveOut(() => loadQuestion(currentQuestionIndex));
        } else {
            alert("Це останнє питання! Натисніть '✓' для отримання результату.");
        }
    });
});

// Функція завантаження тексту питання та варіантів з API
function loadQuestion(index) {
    fetch(`/api/quiz/${index}`)
        .then(res => res.json())
        .then(data => {
            // Оновлюємо текст питання
            document.querySelector('.quiz-question').innerText = data.question;
            
            // Оновлюємо варіанти відповідей
            const options = document.querySelectorAll('.option-row');
            options.forEach((row, i) => {
                row.classList.remove('active');
                // Скидаємо стилі внутрішнього радіо-кружечка
                row.querySelector('.custom-radio').style.background = '#080201';
                
                if (data.options && data.options[i]) {
                    row.style.display = 'flex';
                    row.querySelector('.option-text').innerText = data.options[i];
                } else {
                    row.style.display = 'none'; // Якщо варіантів менше ніж 3
                }
            });

            // Відновлюємо вибір, якщо користувач повернувся назад
            if (selectedAnswers[index] !== undefined) {
                const savedOptIndex = selectedAnswers[index];
                const targetRow = options[savedOptIndex];
                targetRow.classList.add('active');
                targetRow.querySelector('.custom-radio').style.background = '#8b5e3c';
                currentSelectedOption = savedOptIndex;
            } else {
                currentSelectedOption = null;
            }

            // Оновлюємо бейдж статусу (наприклад, "Питання 1 з 5")
            const statusBadge = document.querySelector('.status-badge');
            if(statusBadge) {
                statusBadge.innerHTML = `<span>🧭 Питання ${index + 1} / ${totalQuestions}</span>`;
            }

            animateWaveIn();
            initOptionClicks(); // Переініціалізуємо кліки на нові рядки
        });
}

// Функція для обробки кліків по рядках відповідей (щоб ставилися галочки)
function initOptionClicks() {
    document.querySelectorAll('.option-row').forEach((row, index) => {
        // Очищаємо старі слухачі (клонуванням), щоб уникнути дублювання кліків
        const newRow = row.cloneNode(true);
        row.parentNode.replaceChild(newRow, row);

        newRow.addEventListener('click', () => {
            // Знімаємо виділення з усіх
            document.querySelectorAll('.option-row').forEach(r => {
                r.classList.remove('active');
                r.querySelector('.custom-radio').style.background = '#080201';
                r.querySelector('.custom-radio').innerHTML = '';
            });

            // Додаємо виділення поточному
            newRow.classList.add('active');
            // Робимо ефект "відмітки" (ставимо колір або символ галочки)
            newRow.querySelector('.custom-radio').style.background = '#8b5e3c';
            newRow.querySelector('.custom-radio').innerHTML = '<span style="color:#fff; font-size:10px; display:block; text-align:center; line-height:20px;">✓</span>';
            
            currentSelectedOption = index;
        });
    });
}

function saveCurrentAnswer() {
    if (currentSelectedOption !== null) {
        selectedAnswers[currentQuestionIndex] = currentSelectedOption;
    }
}

function animateWaveIn() {
    document.querySelectorAll('.option-row').forEach(r => { r.classList.remove('wave-out'); r.classList.add('wave-in'); });
}

function animateWaveOut(cb) {
    document.querySelectorAll('.option-row').forEach(r => { r.classList.remove('wave-in'); r.classList.add('wave-out'); });
    setTimeout(cb, 400);
}

// Відправка фінального масиву на бекенд
function sendAnswersToBackend() {
    const userRaw = localStorage.getItem("currentUser");
    let userId = 1; 
    if (userRaw) {
        const user = JSON.parse(userRaw);
        userId = user.id;
    }

    fetch('/api/quiz/result', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            userId: userId,
            answers: selectedAnswers
        })
    })
    .then(res => res.json())
    .then(data => {
        if(data.coffee) {
            const quizCard = document.querySelector('.quiz-card');
            quizCard.innerHTML = `
                <h3 style="color: #e1dbca;">Твій ідеальний вибір знайдено!</h3>
                <h1 style="font-size: 2.2rem; color: #8b5e3c; margin: 20px 0; font-family:'Montserrat',sans-serif;">${data.coffee.name}</h1>
                <p style="font-size: 0.95rem; opacity: 0.8; margin-bottom: 30px; line-height:1.4;">${data.coffee.description}</p>
                
                <div style="display: flex; flex-direction: column; gap: 12px;">
                    <button class="modal-btn primary" id="saveFavBtn" style="width:100%;">⭐ Зберегти в улюблене</button>
                    <button class="modal-btn secondary" onclick="window.location.href='/'" style="width:100%;">На головну</button>
                </div>
            `;
            
            document.getElementById('saveFavBtn').addEventListener('click', () => {
                alert("Додано до улюбленого!");
            });
        }
    })
    .catch(err => console.error("Помилка при отриманні результату:", err));
}
)";
    }

    // ─────────────────────────────────────────────
    //  Хелпери відповідей
    // ─────────────────────────────────────────────
    crow::response textResponse(const std::string& content, const char* contentType, int code = 200) {
        crow::response res(code, content);
        res.set_header("Content-Type", contentType);
        return res;
    }

    void addCorsHeaders(crow::response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    }

    crow::response optionsResponse() {
        crow::response res(200, "ok");
        addCorsHeaders(res);
        return res;
    }

    crow::response fileResponse(const char* fileName, const char* contentType, const std::string& fallback = "") {
        std::string content = readTextFile(fileName);
        if (content.empty()) content = fallback;
        if (content.empty()) return crow::response(404, std::string(fileName) + " not found");
        return textResponse(content, contentType);
    }

    crow::response jsonResponse(crow::json::wvalue data, int code = 200) {
        crow::response res(code, data.dump());
        res.set_header("Content-Type", "application/json; charset=utf-8");
        addCorsHeaders(res);
        return res;
    }

    bool getJsonString(const crow::json::rvalue& body, const char* key, std::string& value) {
        if (!body || !body.has(key)) return false;
        value = std::string(body[key].s());
        return true;
    }

    crow::json::wvalue userToJson(const User& user) {
        crow::json::wvalue j;
        j["id"] = user.getId();
        j["login"] = user.getLogin();
        j["name"] = user.getName();
        j["gmail"] = user.getGmail();
        return j;
    }

    std::string hashPassword(const std::string& password) {
        std::hash<std::string> h;
        return std::to_string(h(password));
    }

    void saveAll(
        CoffeeStorage& coffeeStorage,
        TestStorage& testStorage,
        CoffeeCategoryStorage& categoryStorage,
        CoffeeSelectorStorage& selectorStorage,
        ResultStorage& resultStorage,
        UserStorage& userStorage
    ) {
        coffeeStorage.saveToTwoFiles("coffee.dat", "coffee_backup.dat");
        testStorage.saveToTwoFiles("myTest.dat", "myTest_backup.dat");
        categoryStorage.saveToTwoFiles("coffeeCategory.dat", "coffeeCategory_backup.dat");
        selectorStorage.saveToTwoFiles("coffeeSelector.dat", "coffeeSelector_backup.dat");
        resultStorage.saveToTwoFiles("resultTest.dat", "resultTest_backup.dat");
        userStorage.saveToTwoFiles("user.dat", "user_backup.dat");
    }

} // namespace

// ═════════════════════════════════════════════
//  main
// ═════════════════════════════════════════════
int main() {
    const int MAX = 1000;

    CoffeeStorage         coffeeStorage(MAX);
    TestStorage           testStorage(MAX);
    CoffeeCategoryStorage categoryStorage(MAX);
    CoffeeSelectorStorage selectorStorage(MAX);
    ResultStorage         resultStorage(MAX);
    UserStorage           userStorage(MAX);

    userStorage.loadFromAnyFile("user.dat", "user_backup.dat");
    coffeeStorage.loadFromAnyFile("coffee.dat", "coffee_backup.dat");
    testStorage.loadFromAnyFile("myTest.dat", "myTest_backup.dat");
    categoryStorage.loadFromAnyFile("coffeeCategory.dat", "coffeeCategory_backup.dat");
    selectorStorage.loadFromAnyFile("coffeeSelector.dat", "coffeeSelector_backup.dat");
    resultStorage.loadFromAnyFile("resultTest.dat", "resultTest_backup.dat");

    testStorage.loadDefaultsIfEmpty();
    categoryStorage.loadDefaultsIfEmpty();
    coffeeStorage.loadDefaultsIfEmpty();

    crow::SimpleApp server;

    int defaultCount = 0;
    const Coffee* defaults = getDefaultCoffees(defaultCount);

    for (int i = 0; i < defaultCount; i++) {
        coffeeStorage.addCoffee(defaults[i]);
    }

    // ── Маршрути квізу ──────────────────────────────

    CROW_ROUTE(server, "/api/quiz/count")
        ([&testStorage]() {
        crow::json::wvalue res;
        res["count"] = testStorage.getCount();
        return jsonResponse(res);
            });

    CROW_ROUTE(server, "/api/quiz/answer").methods("POST"_method)
        ([&resultStorage](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");

            if (!body.has("userId") || body["userId"].t() != crow::json::type::Number) {
                return crow::response(400, "userId required");
            }

            int userId = body["userId"].i();

            if (!body.has("answers") || body["answers"].t() != crow::json::type::List) {
                return crow::response(400, "answers must be array");
            }

            auto answers = body["answers"];
            int attemptId = resultStorage.getNextAttemptIdForUser(userId);

            for (size_t i = 0; i < answers.size(); i++) {
                if (answers[i].t() != crow::json::type::Number) continue;

                resultStorage.addAnswerForUserAttempt(
                    userId,
                    attemptId,
                    (int)i,
                    'A' + answers[i].i()
                );
            }

            crow::json::wvalue res;
            res["status"] = "ok";
            return jsonResponse(res);
        }
        catch (const std::exception& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
            return crow::response(500, "Server error");
        }
            });

    CROW_ROUTE(server, "/api/quiz/result").methods("POST"_method)
        ([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        int userId = body["userId"].i();
        auto answers = body["answers"];

        int coffeeCount = coffeeStorage.getCount();
        const Coffee* coffees = coffeeStorage.getByIndex(0);

        int testCount = 0;
        const Test* tests = getDefaultTests(testCount);

        Result results[10];
        int resultCount = std::min((int)answers.size(), 10);

        for (int i = 0; i < resultCount; i++) {
            char choice = 'A' + answers[i].i();
            results[i] = Result(tests[i].getId(), choice);
        }

        int scores[20] = { 0 };
        CoffeeSelector selector;
        selector.calculateScores(scores, results, resultCount, tests, testCount);

        Coffee best;
        if (coffees != nullptr && coffeeCount > 0) {
            best = selector.selectBest(coffees, coffeeCount, scores);
        }

        int attemptId = resultStorage.getNextAttemptIdForUser(userId);

        for (int i = 0; i < resultCount; i++) {
            resultStorage.addAnswerForUserAttempt(
                userId,
                attemptId,
                tests[i].getId(),
                'A' + answers[i].i()
            );
        }

        crow::json::wvalue res;
        res["coffee"]["id"] = best.getId();
        res["coffee"]["name"] = best.getName();
        res["coffee"]["description"] = best.getDescription(); // додай якщо є геттер
        res["coffee"]["strength"] = best.getStrength();
        res["coffee"]["levelRoast"] = best.getLevelRoast();
        res["coffee"]["syrup"] = best.getSyrup();
        res["coffee"]["sugar"] = best.getSugar();
        res["coffee"]["milk"] = best.getMilk();
        res["coffee"]["categoryId"] = best.getCategoryId();
        return jsonResponse(res);
            });
    CROW_ROUTE(server, "/api/quiz/history/<int>")
        ([&resultStorage, &coffeeStorage](int userId) {
        crow::json::wvalue res;
        crow::json::wvalue::list historyList;

        // Збираємо всі спроби цього юзера
        int totalResults = resultStorage.getCount();
        const Result* allResults = resultStorage.data();

        // Групуємо по attemptId — знаходимо унікальні спроби
        int seenAttempts[100];
        int seenCount = 0;

        for (int i = 0; i < totalResults; i++) {
            if (allResults[i].getUserId() != userId) continue;
            int aid = allResults[i].getAttemptId();
            bool found = false;
            for (int j = 0; j < seenCount; j++) {
                if (seenAttempts[j] == aid) { found = true; break; }
            }
            if (!found && seenCount < 100) seenAttempts[seenCount++] = aid;
        }

        for (int a = 0; a < seenCount; a++) {
            int attemptId = seenAttempts[a];
            // Рахуємо скільки відповідей в цій спробі
            int answerCount = 0;
            for (int i = 0; i < totalResults; i++) {
                if (allResults[i].getUserId() == userId && allResults[i].getAttemptId() == attemptId)
                    answerCount++;
            }

            crow::json::wvalue item;
            item["attemptId"] = attemptId;
            item["answerCount"] = answerCount;
            // Кава поки що — заглушка, поки не зберігається coffeeId в Result
            item["coffee"]["name"] = "—";
            historyList.push_back(std::move(item));
        }

        res["history"] = std::move(historyList);
        return jsonResponse(res);
            });
    CROW_ROUTE(server, "/profile")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\profile.html", "text/html; charset=utf-8");
        });

    CROW_ROUTE(server, "/catalog")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\catalog.html", "text/html; charset=utf-8");
        });


    CROW_ROUTE(server, "/result")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\result.html", "text/html; charset=utf-8");
        });
    CROW_ROUTE(server, "/api/coffee/all")
        ([&coffeeStorage]() {
        crow::json::wvalue res;
        crow::json::wvalue::list list;
        int count = coffeeStorage.getCount();
        for (int i = 0; i < count; i++) {
            const Coffee* c = coffeeStorage.getByIndex(i);
            if (!c) continue;
            crow::json::wvalue item;
            item["id"] = c->getId();
            item["name"] = c->getName();
            item["description"] = c->getDescription();
            item["strength"] = c->getStrength();
            item["levelRoast"] = c->getLevelRoast();
            item["syrup"] = c->getSyrup();
            item["sugar"] = c->getSugar();
            item["milk"] = c->getMilk();
            item["categoryId"] = c->getCategoryId();
            list.push_back(std::move(item));
        }
        res["coffees"] = std::move(list);
        return jsonResponse(res);
            });

    CROW_ROUTE(server, "/api/quiz/<int>")
        ([&testStorage](int index) {
        crow::json::wvalue res;
        const Test* t = testStorage.getAt(index);

        if (!t) {
            res["error"] = "Invalid index";
            res["options"] = crow::json::wvalue::list();
            res["question"] = "";
            return jsonResponse(res, 404);
        }

        res["question"] = t->getQuestionText();
        res["options"][0] = t->getAnswerTextForChoice('A');
        res["options"][1] = t->getAnswerTextForChoice('B');
        res["options"][2] = t->getAnswerTextForChoice('C');

        return jsonResponse(res);
            });

    // ── Роздача статичних файлів ──────────────────────────────

    CROW_ROUTE(server, "/")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\main.html", "text/html; charset=utf-8", defaultIndexHtml());
        });

    CROW_ROUTE(server, "/style.css")([]() {
        return fileResponse("C:\\web-coursoviy\\css\\style.css", "text/css; charset=utf-8", defaultCss());
        });

    CROW_ROUTE(server, "/script.js")([]() {
        return fileResponse("C:\\web-coursoviy\\js\\script.js", "application/javascript; charset=utf-8");
        });

    CROW_ROUTE(server, "/test")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\test.html", "text/html; charset=utf-8", defaultTestHtml());
        });

    CROW_ROUTE(server, "/test.css")([]() {
        return fileResponse("C:\\web-coursoviy\\css\\test.css", "text/css; charset=utf-8", defaultTestCss());
        });

    CROW_ROUTE(server, "/test.js")([]() {
        return fileResponse("C:\\web-coursoviy\\js\\test.js", "application/javascript; charset=utf-8", defaultTestJs());
        });

    CROW_ROUTE(server, "/meals")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\meals.html", "text/html; charset=utf-8", defaultIndexHtml());
        });

    CROW_ROUTE(server, "/img/<string>")([](const std::string& fileName) {
        std::string path = "C:\\web-coursoviy\\img\\" + fileName;

        // Визначаємо Content-Type по розширенню
        std::string contentType = "application/octet-stream";
        if (fileName.size() > 4) {
            std::string ext = fileName.substr(fileName.size() - 4);
            if (ext == ".svg") contentType = "image/svg+xml; charset=utf-8";
            else if (ext == ".jpg" || fileName.substr(fileName.size() - 5) == ".jpeg")
                contentType = "image/jpeg";
            else if (ext == ".png") contentType = "image/png";
            else if (ext == ".gif") contentType = "image/gif";
            else if (ext == ".ico") contentType = "image/x-icon";
        }

        // Для бінарних файлів читаємо інакше
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) return crow::response(404, "Image not found: " + fileName);

        std::ostringstream buffer;
        buffer << file.rdbuf();

        crow::response res(200, buffer.str());
        res.set_header("Content-Type", contentType);
        return res;
        });

    // ── Службові API ───────────────────────────────────

    CROW_ROUTE(server, "/api/test")([]() {
        crow::json::wvalue res;
        res["status"] = "ok";
        res["message"] = "Hello from Crow REST API";
        return jsonResponse(res);
        });

    CROW_ROUTE(server, "/api/stats")([&](const crow::request&) {
        crow::json::wvalue res;
        res["coffeeCount"] = coffeeStorage.getCount();
        res["testCount"] = testStorage.getCount();
        res["categoryCount"] = categoryStorage.getCount();
        res["selectorCount"] = selectorStorage.getCount();
        res["resultCount"] = resultStorage.getCount();
        res["userCount"] = userStorage.getCount();
        return jsonResponse(res);
        });

    CROW_ROUTE(server, "/api/save")([&](const crow::request&) {
        saveAll(coffeeStorage, testStorage, categoryStorage, selectorStorage, resultStorage, userStorage);
        crow::json::wvalue res;
        res["status"] = "saved";
        return jsonResponse(res);
        });

    // ── Авторизація та Реєстрація ──────────────────────────────

    CROW_ROUTE(server, "/register.html")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\register.html", "text/html; charset=utf-8");
        });

    CROW_ROUTE(server, "/api/register").methods(crow::HTTPMethod::Post)
        ([&userStorage](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string login, password, name, gmail;

        if (!getJsonString(body, "login", login) || !getJsonString(body, "password", password)) {
            crow::json::wvalue err;
            err["error"] = "login/password required";
            return jsonResponse(err, 400);
        }

        if (userStorage.findByLogin(login.c_str()) != -1) {
            crow::json::wvalue err;
            err["error"] = "user exists";
            return jsonResponse(err, 409);
        }

        if (!getJsonString(body, "name", name)) name = login;
        if (!getJsonString(body, "gmail", gmail)) gmail = "";

        std::string hashed = hashPassword(password);
        int id = userStorage.getCount() + 1;

        User user(id, name.c_str(), login.c_str(), gmail.c_str(), hashed.c_str(), "");
        if (!userStorage.registerUser(user)) {
            crow::json::wvalue err;
            err["error"] = "cannot register";
            return jsonResponse(err, 500);
        }

        userStorage.saveToTwoFiles("user.dat", "user_backup.dat");

        crow::json::wvalue res;
        res["status"] = "ok";
        res["userId"] = user.getId();
        return jsonResponse(res);
            });

    CROW_ROUTE(server, "/login.html")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\login.html", "text/html; charset=utf-8");
        });
    CROW_ROUTE(server, "/catalog,html")([]() {
        return fileResponse("C:\\web-coursoviy\\html\\catalog.html", "text/html; charset=utf-8");
        });

    CROW_ROUTE(server, "/api/login").methods(crow::HTTPMethod::Post)
        ([&userStorage](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string login, password;

        if (!getJsonString(body, "login", login) || !getJsonString(body, "password", password)) {
            return jsonResponse({ {"error","bad request"} }, 400);
        }

        std::string hashed = hashPassword(password);
        User user;

        if (!userStorage.loginUser(login.c_str(), hashed.c_str(), user)) {
            return jsonResponse({ {"error","wrong login"} }, 401);
        }

        crow::json::wvalue res;
        res["status"] = "ok";
        res["userId"] = user.getId();
        return jsonResponse(res);
            });


    CROW_ROUTE(server, "/wave-bg.js")([]() {
        return fileResponse("C:\\web-coursoviy\\js\\wave-bg.js", "application/javascript; charset=utf-8");
        });
    //профіль та історія тестувань + улюблене

    // ─────────────────────────────────────────────
    // 1. Отримання історії тестів користувача
    // ─────────────────────────────────────────────
    CROW_ROUTE(server, "/api/user/history/<int>")
        ([&coffeeStorage, &resultStorage](int userId) {
        crow::json::wvalue res;
        crow::json::wvalue::list historyList;

        // Припустимо, ми знаємо, яка кава була підібрана (або беремо з логів)
        // Для демонстрації викладачу: дістаємо каву з ID, який зберігся у сесії/результатах.
        // Наприклад, користувачу з id=1 підійшла кава з id=3 (Latte)

        // Шукаємо каву в нашому каталозі за ID
        int cId = 3; // Приклад захардкодженного ID, заміни на логіку з resultStorage
        const Coffee* foundCoffee = nullptr;

        int coffeeCount = coffeeStorage.getCount();
        const Coffee* coffees = coffeeStorage.getByIndex(0);
        for (int i = 0; i < coffeeCount; i++) {
            if (coffees[i].getId() == cId) {
                foundCoffee = &coffees[i];
                break;
            }
        }

        crow::json::wvalue item;
        item["date"] = "02.06.2026";
        item["coffeeName"] = foundCoffee ? foundCoffee->getName() : "Невідома кава";
        historyList.push_back(item);

        res["history"] = std::move(historyList);
        return jsonResponse(res);
            });

    // ─────────────────────────────────────────────
    // 2. Додавання кави до улюбленого (Favorites)
    // ─────────────────────────────────────────────
    CROW_ROUTE(server, "/api/user/favorites/add").methods(crow::HTTPMethod::Post)
        ([&userStorage](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("coffeeId")) {
            return crow::response(400, "userId and coffeeId required");
        }

        int userId = body["userId"].i();
        int coffeeId = body["coffeeId"].i();

        // Логіка додавання. Якщо у твоєму класі User або всередині UserStorage 
        // є масив/метод для збереження зв'язку користувач-кава:
        // наприклад: userStorage.addFavoriteCoffee(userId, coffeeId);

        userStorage.saveToTwoFiles("user.dat", "user_backup.dat");

        crow::json::wvalue res;
        res["status"] = "ok";
        res["message"] = "Каву додано до улюбленого";
        return jsonResponse(res);
            });

    // ─────────────────────────────────────────────
    // 3. Отримання списку улюбленої кави користувача
    // ─────────────────────────────────────────────
    CROW_ROUTE(server, "/api/user/favorites/<int>")
        ([&userStorage, &coffeeStorage](int userId) {
        crow::json::wvalue res;
        crow::json::wvalue::list favList;

        // Логіка вибірки улюблених кав користувача із завантаженням їхніх імен:
        // Перебираємо кави з масиву улюблених для цього userId

        crow::json::wvalue mockFav;
        mockFav["id"] = 1;
        mockFav["name"] = "Капучино";
        favList.push_back(mockFav);

        res["favorites"] = std::move(favList);
        return jsonResponse(res);
            });

    // ── Вивід інформації ────────────────────────────────
    std::cout << "Server started!\n";
    std::cout << "Open:        http://localhost:18080/\n";
    std::cout << "Quiz page:   http://localhost:18080/test\n";
    std::cout << "Meals page:  http://localhost:18080/meals\n";

    server.loglevel(crow::LogLevel::Debug);
    server.port(18080).bindaddr("127.0.0.1").run();

    std::cout << "Server stopped!\n";
    system("pause");

    saveAll(coffeeStorage, testStorage, categoryStorage, selectorStorage, resultStorage, userStorage);
    std::cout << "Saved successfully!\n";
    return 0;
}