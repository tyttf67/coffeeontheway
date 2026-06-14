function goLogin() {
    window.location.href = "/login.html";
}

document.addEventListener("DOMContentLoaded", () => {
    const registerBtn = document.getElementById("registerBtn");
    
    if (registerBtn) {
        registerBtn.addEventListener("click", async (e) => {
            e.preventDefault();

            const login = document.getElementById("login").value.trim();
            const password = document.getElementById("password").value;

            if (!login || !password) {
                alert("Заповніть всі поля");
                return;
            }

            try {
                const res = await fetch("/api/register", {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify({ login, password })
                });

                const data = await res.json();

                if (data.userId) {
                    const userObj = { id: data.userId, login: login };
                    localStorage.setItem("currentUser", JSON.stringify(userObj));
                    
                    alert("Реєстрація успішна!");
                    window.location.href = "/";
                } else {
                    alert(data.error || "Помилка реєстрації");
                }
            } catch (error) {
                alert("Помилка сервера");
            }
        });
    }
});