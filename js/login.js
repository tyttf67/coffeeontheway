// Функція перенаправлення на сторінку реєстрації
function goRegister() {
    window.location.href = "/register.html"; // або як називається твій файл реєстрації
}

// Чекаємо, поки завантажиться сторінка, щоб знайти кнопку
document.addEventListener("DOMContentLoaded", () => {
    
    const loginBtn = document.getElementById("loginBtn");
    
    if (loginBtn) {
        loginBtn.addEventListener("click", async (e) => {
            e.preventDefault(); // Захист від перезавантаження

            const login = document.getElementById("login").value.trim();
            const password = document.getElementById("password").value;

            if (!login || !password) {
                alert("Заповніть всі поля");
                return;
            }

            try {
                const res = await fetch("/api/login", {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify({ login, password })
                });

                const data = await res.json();

                if (data.userId) {
                    // Зберігаємо користувача в систему
                    const userObj = { id: data.userId, login: login };
                    localStorage.setItem("currentUser", JSON.stringify(userObj));
                    
                    // Перенаправляємо на головну сторінку
                    window.location.href = "/";
                } else {
                    alert("Невірний логін або пароль");
                }
            } catch (error) {
                alert("Помилка сервера або невірні дані");
            }
        });
    }
});