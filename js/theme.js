/**
 * theme.js — підключати на ВСІХ сторінках.
 * Перемикач (#themeToggle) є тільки на головній.
 * Всі інші сторінки просто читають збережену тему.
 */
(function () {
  var KEY = 'site-theme';

  function getSaved() {
    return localStorage.getItem(KEY) === 'dark' ? 'dark' : 'light';
  }

  function apply(theme) {
    document.documentElement.setAttribute('data-theme', theme);
    localStorage.setItem(KEY, theme);
  }

  // Застосовуємо ОДРАЗУ — до рендеру, без мигання
  apply(getSaved());

  document.addEventListener('DOMContentLoaded', function () {
    var toggle = document.getElementById('themeToggle');
    if (!toggle) return;

    toggle.addEventListener('click', function () {
      var current = document.documentElement.getAttribute('data-theme') || 'light';
      apply(current === 'dark' ? 'light' : 'dark');
    });
  });
})();