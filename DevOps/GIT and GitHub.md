## Step 1: Install Git and Set Up GitHub Account

### A. Download and Install Git

1. Go to [https://git-scm.com/](https://git-scm.com/) and download **Git for Windows**.
2. Run the installer and proceed with the default settings (you can customize if needed).
3. Alternatively, if using **WSL (Linux Terminal)**:

   ```bash
   sudo apt update
   sudo apt install git -y
   ```

### B. Configure Git

After installation, open **Git Bash** and run:

```bash
git --version                          # Check if Git is installed
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
git config --list                      # Verify your configuration
```

---

## Step 2: Create a Repository on GitHub

1. Go to [https://github.com](https://github.com) and **log in or create an account**.
2. Click the **"+"** icon → **New repository**.
3. Add a **README.md** file if prompted.
4. Upload additional files from your desktop using the **"Add file"** → **"Upload files"** option.
5. To view version history, click the **clock icon (History)** in the repo.

---

## Step 3: Use Git Bash to Track Version History

### A. Clone an Existing GitHub Repository Locally

1. Open Git Bash and run:

   ```bash
   git clone https://github.com/your-username/your-repo.git
   cd your-repo
   ```
2. Make changes:

   ```bash
   echo "New changes" >> file.txt
   git add .                                 # Stage all changes
   git commit -m "Updated file"              # Commit with a message
   git push origin main                      # Push changes to GitHub
   ```

---

### B. Upload a Local Project to GitHub

1. Create a **new folder** and a file inside it.

2. Right-click in the folder → **Open Git Bash here** and run:

   ```bash
   git init                                   # Initialize Git in folder
   git add .
   git commit -m "Added files"
   git remote add origin https://github.com/your-username/your-repo.git
   git push -u origin main                    # First push with upstream
   ```

3. If someone else edits the file on GitHub or you do it directly via GitHub UI:

   ```bash
   git pull origin main                       # Pull latest changes locally
   ```

---

### C. Working with Branches

1. Create and switch to a new branch:

   ```bash
   git checkout -b new-feature
   ```
2. Make changes or add a file, then:

   ```bash
   git add .
   git commit -m "New feature done"
   ```
3. Switch back to the main branch and merge:

   ```bash
   git checkout main
   git merge new-feature
   ```
