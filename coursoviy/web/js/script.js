const API_BASE_URL = "";

const appState = {
    currentUser: readCurrentUser()
};

function $(id) {
    return document.getElementById(id);
}

function setText(id, value) {
    const element = $(id);
    if (element) {
        element.textContent = value;
    }
}

function setHtml(id, value) {
    const element = $(id);
    if (element) {
        element.innerHTML = value;
    }
}

function showMessage(message, type = "info") {
    const messageBox = $("message") || $("statusMessage") || $("appMessage");
    if (!messageBox) {
        console.log(message);
        return;
    }

    messageBox.textContent = message;
    messageBox.dataset.type = type;
}

async function requestJson(path, options = {}) {
    const response = await fetch(`${API_BASE_URL}${path}`, {
        headers: {
            "Content-Type": "application/json",
            ...(options.headers || {})
        },
        ...options
    });

    const text = await response.text();
    const data = text ? JSON.parse(text) : {};

    if (!response.ok) {
        throw new Error(data.message || data.error || `Request failed: ${response.status}`);
    }

    return data;
}

async function fetchData() {
    try {
        const stats = await requestJson("/api/stats");
        renderStats(stats);
        showMessage("Дані завантажено", "success");
    } catch (error) {
        showMessage(`Не вдалося завантажити дані: ${error.message}`, "error");
    }
}

function renderStats(stats) {
    setText("coffeeCount", stats.coffeeCount ?? 0);
    setText("testCount", stats.testCount ?? 0);
    setText("categoryCount", stats.categoryCount ?? 0);
    setText("selectorCount", stats.selectorCount ?? 0);
    setText("resultCount", stats.resultCount ?? 0);
    setText("userCount", stats.userCount ?? 0);

    setHtml("stats", `
        <div class="stat-item">Кава: ${stats.coffeeCount ?? 0}</div>
        <div class="stat-item">Тести: ${stats.testCount ?? 0}</div>
        <div class="stat-item">Категорії: ${stats.categoryCount ?? 0}</div>
        <div class="stat-item">Підбірки: ${stats.selectorCount ?? 0}</div>
        <div class="stat-item">Результати: ${stats.resultCount ?? 0}</div>
        <div class="stat-item">Користувачі: ${stats.userCount ?? 0}</div>
    `);
}

async function testServer() {
    try {
        const data = await requestJson("/api/test");
        showMessage(data.message || "Сервер працює", "success");
    } catch (error) {
        showMessage(`Сервер не відповідає: ${error.message}`, "error");
    }
}

async function saveData() {
    try {
        const data = await requestJson("/api/save");
        showMessage(data.status === "saved" ? "Дані збережено" : "Запит на збереження виконано", "success");
    } catch (error) {
        showMessage(`Не вдалося зберегти дані: ${error.message}`, "error");
    }
}

async function registerUser(login, password) {
    return requestJson("/api/register", {
        method: "POST",
        body: JSON.stringify({ login, password })
    });
}

async function loginUser(login, password) {
    return requestJson("/api/login", {
        method: "POST",
        body: JSON.stringify({ login, password })
    });
}

function readCurrentUser() {
    try {
        return JSON.parse(localStorage.getItem("currentUser"));
    } catch {
        return null;
    }
}

function saveCurrentUser(user) {
    appState.currentUser = user;
    localStorage.setItem("currentUser", JSON.stringify(user));
    renderCurrentUser();
}

function logoutUser() {
    appState.currentUser = null;
    localStorage.removeItem("currentUser");
    renderCurrentUser();
    showMessage("Ви вийшли з акаунта", "success");
}

function renderCurrentUser() {
    const user = appState.currentUser;
    const label = user?.login || user?.name || "Гість";

    setText("currentUser", label);
    setText("userName", label);

    const authPanel = $("authPanel");
    const profilePanel = $("profilePanel");

    if (authPanel) {
        authPanel.hidden = Boolean(user);
    }

    if (profilePanel) {
        profilePanel.hidden = !user;
    }
}

function bindStatsActions() {
    const refreshButton = $("refreshStatsBtn") || $("loadStatsBtn");
    if (refreshButton) {
        refreshButton.addEventListener("click", fetchData);
    }

    const testButton = $("testServerBtn");
    if (testButton) {
        testButton.addEventListener("click", testServer);
    }

    const saveButton = $("saveDataBtn");
    if (saveButton) {
        saveButton.addEventListener("click", saveData);
    }
}

function bindAuthForms() {
    const registerForm = $("registerForm");
    if (registerForm) {
        registerForm.addEventListener("submit", async (event) => {
            event.preventDefault();

            const login = $("registerLogin")?.value.trim();
            const password = $("registerPassword")?.value;

            if (!login || !password) {
                showMessage("Введіть логін і пароль для реєстрації", "error");
                return;
            }

            try {
                const result = await registerUser(login, password);
                showMessage(result.message || "Реєстрація успішна", "success");
                registerForm.reset();
            } catch (error) {
                showMessage(`Реєстрація поки не працює: ${error.message}`, "error");
            }
        });
    }

    const loginForm = $("loginForm");
    if (loginForm) {
        loginForm.addEventListener("submit", async (event) => {
            event.preventDefault();

            const login = $("loginLogin")?.value.trim();
            const password = $("loginPassword")?.value;

            if (!login || !password) {
                showMessage("Введіть логін і пароль для входу", "error");
                return;
            }

            try {
                const result = await loginUser(login, password);
                saveCurrentUser(result.user || { login });
                showMessage(result.message || "Вхід виконано", "success");
                loginForm.reset();
            } catch (error) {
                showMessage(`Авторизація поки не працює: ${error.message}`, "error");
            }
        });
    }

    const logoutButton = $("logoutBtn");
    if (logoutButton) {
        logoutButton.addEventListener("click", logoutUser);
    }
}

function initApp() {
    bindStatsActions();
    bindAuthForms();
    renderCurrentUser();
    fetchData();
}

document.addEventListener("DOMContentLoaded", initApp);
