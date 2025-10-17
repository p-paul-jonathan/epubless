# epubless

> Read `.epub` books right from your terminal — fast, clean, and written entirely in C.

---

## 📘 Overview

**epubless** is a minimalist terminal EPUB reader.
It unpacks, parses, and displays reflowable EPUB content directly in your terminal.
No GUI, no browser engine, no fluff — just pure text and focus.

---

## ✨ Features

- 📚 Reads standard EPUB 2/3 books
- 🔍 Parses `container.xml`, `package.opf`, and `nav.xhtml` or `toc.ncx`
- 🧭 Navigate by chapter, page, or table of contents
- 🪶 Reflow text to terminal width
- 🎨 Basic styling (bold, italic, headings) using ANSI colors
- 🧠 Bookmarks and progress tracking
- ⌨️ Vi-style navigation: `j/k`, `PgUp/PgDn`, `/` search, `q` quit

---

## 🧰 Build

**Dependencies**
- `libzip` — for EPUB (ZIP) extraction
- `libxml2` — for XML/XHTML parsing
- `ncurses` — for terminal UI

**Build example:**
```bash
sudo apt install libzip-dev libxml2-dev libncurses-dev
git clone https://github.com/yourname/epubless.git
cd epubless
make
```

## Features

### 🧭 Navigation & Reading

#### ✅ (you already have)
- h / ← — previous chapter
- l / → — next chapter
- j / ↓ — scroll down
- k / ↑ — scroll up

#### 🆕 suggestions:
- gg — go to start of book
- G — go to end of book
- Ctrl+d / Ctrl+u — half-page down / up (like vim)
- : → command mode prompt (enter any : commands)
- / → search forward
- n / N — next / previous search result

### 🧷 Bookmarks & Contents

#### ✅ (you already have)
- :bookmark / :b — bookmark current page
- :bookmarks — list bookmarks
- :contents — go to table of contents

#### 🆕 suggestions:
- :goto <chapter> — jump directly to a chapter by number or name
- :open <bookmark> — jump to a saved bookmark
- :delbookmark <n> — delete a bookmark by index

### ⚙️ Display & UI

#### 🆕 ideas:
- :theme <name> — switch theme (e.g. light, dark, sepia)
- + / - — increase / decrease text width (wrap width)
- :wrap <on|off> — toggle word wrapping (for poetry or code snippets)
- :status — show metadata (title, author, current location %)
- :progress — show reading progress visually (like a bar or % in status line)

### 🔍 Search & Metadata

#### 🆕 ideas:
- :meta — show EPUB metadata (title, author, publisher, date)
- :info — same as above but also shows file path, encoding, current chapter index

### 💾 Session & Settings

#### 🆕 ideas:
- :save — save current session (position + bookmarks)
- :restore — restore last session automatically on startup
- :config — open config file in $EDITOR
- :reload — reload book (useful after re-converting EPUB)

### 💡 Experimental / Fun

#### 🆕 optional but cool:
- :quote — copy current line/paragraph to clipboard
- :stats — show how many pages/words read so far
- :timer — reading timer / focus mode
- :export <path> — export current chapter as plain text
