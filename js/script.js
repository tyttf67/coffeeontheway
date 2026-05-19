const API_BASE_URL = "http://localhost:18080";

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

function setMessage(message, type = "info") {
    const element = $("message");
    if (!element) {
        return;
    }

    element.textContent = message;
    element.dataset.type = type;
}

function setServerStatus(isOnline) {
    const element = $("serverStatus");
    if (!element) {
        return;
    }

    element.textContent = isOnline ? "server online" : "server offline";
    element.classList.toggle("online", isOnline);
    element.classList.toggle("offline", !isOnline);
}

async function requestJson(path, options = {}) {
    const response = await fetch(`${API_BASE_URL}${path}`, {
        headers: {
            ...(options.headers || {})
        },
        ...options
    });

    const text = await response.text();
    const data = text ? JSON.parse(text) : {};

    if (!response.ok) {
        throw new Error(data.message || data.error || `HTTP ${response.status}`);
    }

    return data;
}

async function testServer() {
    try {
        const data = await requestJson("/api/test");
        setServerStatus(true);
        setMessage(data.message || "Сервер працює", "success");
    } catch (error) {
        setServerStatus(false);
        setMessage(`Сервер не відповідає: ${error.message}`, "error");
    }
}

async function loadStats() {
    try {
        const stats = await requestJson("/api/stats");
        renderStats(stats);
        setServerStatus(true);
        setMessage("Дані з backend завантажено", "success");
    } catch (error) {
        setServerStatus(false);
        setMessage(`Не вдалося завантажити статистику: ${error.message}`, "error");
    }
}

function renderStats(stats) {
    setText("coffeeCount", stats.coffeeCount ?? 0);
    setText("testCount", stats.testCount ?? 0);
    setText("categoryCount", stats.categoryCount ?? 0);
    setText("selectorCount", stats.selectorCount ?? 0);
    setText("resultCount", stats.resultCount ?? 0);
    setText("userCount", stats.userCount ?? 0);
}

async function saveData() {
    try {
        const data = await requestJson("/api/save");
        setMessage(data.status === "saved" ? "Дані збережено" : "Запит виконано", "success");
    } catch (error) {
        setMessage(`Не вдалося зберегти дані: ${error.message}`, "error");
    }
}

async function registerUser(login, password) {
    return requestJson("/api/register", {
        method: "POST",
        headers: {
            "Content-Type": "text/plain;charset=UTF-8"
        },
        body: JSON.stringify({ login, password })
    });
}

async function loginUser(login, password) {
    return requestJson("/api/login", {
        method: "POST",
        headers: {
            "Content-Type": "text/plain;charset=UTF-8"
        },
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
    setMessage("Ви вийшли з акаунта", "success");
}

function renderCurrentUser() {
    const user = appState.currentUser;
    setText("currentUser", user?.login || user?.name || "Гість");

    const authPanel = $("authPanel");
    const profilePanel = $("profilePanel");

    if (authPanel) {
        authPanel.hidden = Boolean(user);
    }

    if (profilePanel) {
        profilePanel.hidden = !user;
    }
}

function bindEvents() {
    $("refreshStatsBtn")?.addEventListener("click", loadStats);
    $("testServerBtn")?.addEventListener("click", testServer);
    $("saveDataBtn")?.addEventListener("click", saveData);
    $("logoutBtn")?.addEventListener("click", logoutUser);

    $("registerForm")?.addEventListener("submit", async (event) => {
        event.preventDefault();

        const login = $("registerLogin")?.value.trim();
        const password = $("registerPassword")?.value;

        if (!login || !password) {
            setMessage("Введіть логін і пароль для реєстрації", "error");
            return;
        }

        try {
            const result = await registerUser(login, password);
            saveCurrentUser(result.user || { login });
            event.target.reset();
            setMessage(result.message || "Реєстрація успішна", "success");
            loadStats();
        } catch (error) {
            setMessage(`Помилка реєстрації: ${error.message}`, "error");
        }
    });

    $("loginForm")?.addEventListener("submit", async (event) => {
        event.preventDefault();

        const login = $("loginLogin")?.value.trim();
        const password = $("loginPassword")?.value;

        if (!login || !password) {
            setMessage("Введіть логін і пароль для входу", "error");
            return;
        }

        try {
            const result = await loginUser(login, password);
            saveCurrentUser(result.user || { login });
            event.target.reset();
            setMessage(result.message || "Вхід виконано", "success");
        } catch (error) {
            setMessage(`Помилка входу: ${error.message}`, "error");
        }
    });
}

function init() {
    bindEvents();
    renderCurrentUser();
    testServer();
    loadStats();
}

document.addEventListener("DOMContentLoaded", init);
