const appState = { currentUser: readCurrentUser() };

function $(id) { return document.getElementById(id); }
function setText(id, t) { const e = $(id); if(e) e.textContent = t; }

function showMessage(text, type) {
    type = type || 'info';
    const el = $('message');
    if (el) { el.textContent = text; el.className = 'message ' + type; }
}

async function requestJson(url, options) {
    options = options || {};
    const resp = await fetch(url, Object.assign({}, options, {
        headers: Object.assign({'Content-Type':'application/json'}, options.headers || {})
    }));
    if (!resp.ok) {
        const err = await resp.json().catch(() => ({}));
        throw new Error(err.error || ('Помилка: ' + resp.status));
    }
    return resp.json();
}

function readCurrentUser() {
    try { return JSON.parse(localStorage.getItem('currentUser')); } catch(e) { return null; }
}

function saveCurrentUser(user) {
    appState.currentUser = user;
    localStorage.setItem('currentUser', JSON.stringify(user));
    renderCurrentUser();
}

function logoutUser() {
    appState.currentUser = null;
    localStorage.removeItem('currentUser');
    renderCurrentUser();
    showMessage('Ви вийшли з акаунта', 'success');
}

function renderCurrentUser() {
    const user = appState.currentUser;
    const label = user && user.login ? user.login : 'Гість';
    setText('currentUser', label);
    setText('userName', label);
    const authPanel    = $('authPanel');
    const profilePanel = $('profilePanel');
    if (authPanel)    authPanel.style.display    = user ? 'none' : '';
    if (profilePanel) profilePanel.style.display = user ? ''     : 'none';
    if ($('profileName') && user) $('profileName').textContent = label;
}

async function loadStats() {
    try {
        const stats = await requestJson('/api/stats');
        const c = $('stats');
        if (c) c.innerHTML =
            '<div><b>Кава:</b> ' + stats.coffeeCount + '</div>' +
            '<div><b>Тести:</b> ' + stats.testCount + '</div>' +
            '<div><b>Користувачі:</b> ' + stats.userCount + '</div>' +
            '<div><b>Результати:</b> ' + stats.resultCount + '</div>';
    } catch(e) { console.error('Статистика:', e); }
}

function openAuthModal()  { const m = $('authModal'); if(m) m.classList.add('active'); }
function closeAuthModal() { const m = $('authModal'); if(m) m.classList.remove('active'); }

// ── Пошук ──────────────────────────────────────────
let catalogCoffees = [];

window.openSearch = async function() {
    const panel = $('searchPanel');
    const input = $('liveSearchInput');
    if (!panel || !input) return;
    panel.style.display = 'block';
    input.focus();
    if (!catalogCoffees.length) {
        try {
            const data = await fetch('/api/coffee/all').then(r => r.json());
            catalogCoffees = data.coffees || [];
        } catch(e) {}
    }
};

window.closeSearch = function() {
    const panel = $('searchPanel');
    const input = $('liveSearchInput');
    const results = $('searchResults');
    if (panel)   panel.style.display = 'none';
    if (input)   input.value = '';
    if (results) results.innerHTML = '';
};

window.goToCoffee = function(id) {
    window.closeSearch();
    sessionStorage.setItem('openCoffeeId', id);
    window.location.href = '/catalog';
};

function renderSearchResults(query) {
    const container = $('searchResults');
    if (!container) return;
    if (!query.trim()) { container.innerHTML = ''; return; }
    const matches = catalogCoffees.filter(c =>
        c.name.toLowerCase().includes(query.toLowerCase())
    );
    if (!matches.length) {
        container.innerHTML = '<p style="color:rgba(240,224,204,0.45);font-size:13px;text-align:center;padding:12px 0;">Нічого не знайдено</p>';
        return;
    }
    container.innerHTML = matches.map(c => `
        <div onclick="goToCoffee(${c.id})"
    [data-theme="dark"] style="padding:12px 16px;border-radius:30px;cursor:pointer;
                      background: var(--surface);
  backdrop-filter: blur(10px) saturate(110%);
  -webkit-backdrop-filter: blur(10px) saturate(110%);
  border: 1px solid var(--border);font-family:'Roboto',Arial,sans-serif;font-size:14px;
                    transition:filter 0.2s;"
             onmouseover="this.style.filter='brightness(1.2)'"
             onmouseout="this.style.filter='none'">
            ${c.name}
        </div>
    `).join('');
}

// ── Ініціалізація ──────────────────────────────────
document.addEventListener('DOMContentLoaded', function() {

    // Пошуковий input
    const searchInput = $('liveSearchInput');
    if (searchInput) {
        searchInput.addEventListener('input', () => renderSearchResults(searchInput.value));
    }

    // Кнопка профілю
    document.querySelectorAll('.profile-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            const user = localStorage.getItem('currentUser');
            window.location.href = user ? '/profile' : '/login';
        });
    });

    // Статистика
    const refreshBtn = $('refreshStatsBtn') || $('loadStatsBtn');
    if (refreshBtn) refreshBtn.addEventListener('click', loadStats);

    if ($('testServerBtn')) $('testServerBtn').addEventListener('click', async function() {
        try { const r = await requestJson('/api/test'); showMessage('Сервер: ' + r.message, 'success'); }
        catch(e) { showMessage('Помилка: ' + e.message, 'error'); }
    });

    if ($('saveDataBtn')) $('saveDataBtn').addEventListener('click', async function() {
        try { const r = await requestJson('/api/save'); if(r.status === 'saved') showMessage('Збережено!', 'success'); }
        catch(e) { showMessage('Помилка: ' + e.message, 'error'); }
    });

    // Форма реєстрації
    const regForm = $('registerForm');
    if (regForm) regForm.addEventListener('submit', async function(e) {
        e.preventDefault();
        const login = $('registerLogin') && $('registerLogin').value.trim();
        const pass  = $('registerPassword') && $('registerPassword').value;
        try {
            await requestJson('/api/register', {method:'POST', body: JSON.stringify({login, password: pass})});
            showMessage('Реєстрація успішна! Увійдіть.', 'success');
            regForm.reset();
        } catch(err) { showMessage(err.message, 'error'); }
    });

    // Форма входу
    const loginForm = $('loginForm');
    if (loginForm) loginForm.addEventListener('submit', async function(e) {
        e.preventDefault();
        const login = $('loginLogin') && $('loginLogin').value.trim();
        const pass  = $('loginPassword') && $('loginPassword').value;
        try {
            const res = await requestJson('/api/login', {method:'POST', body: JSON.stringify({login, password: pass})});
            saveCurrentUser({id: res.userId, login});
            showMessage('Вхід виконано!', 'success');
            loginForm.reset();
        } catch(err) { showMessage(err.message, 'error'); }
    });

    if ($('logoutBtn')) $('logoutBtn').addEventListener('click', logoutUser);

    // Модалка
    const closeBtn = $('closeModalBtn');
    if (closeBtn) closeBtn.addEventListener('click', closeAuthModal);
    const modal = $('authModal');
    if (modal) modal.addEventListener('click', function(e) { if(e.target === modal) closeAuthModal(); });

    // Кнопка "Почати тест"
    const startBtn = $('startTestBtn');
    if (startBtn) startBtn.addEventListener('click', function(e) {
        e.preventDefault();
        if (localStorage.getItem('currentUser')) window.location.href = '/test';
        else openAuthModal();
    });
  const input = $('liveSearchInput');
const clearBtn = $('clearSearchBtn');

if (input && clearBtn) {

    input.addEventListener('input', () => {
        renderSearchResults(input.value);

        // показати кнопку тільки якщо є текст
        clearBtn.style.display = input.value ? 'block' : 'none';
    });

    clearBtn.addEventListener('click', () => {
        input.value = '';
        renderSearchResults('');
        input.focus();
        clearBtn.style.display = 'none';
    });
}
    renderCurrentUser();
    loadStats();
});