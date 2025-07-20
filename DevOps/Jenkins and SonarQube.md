## **Step 1: Install Java JDK 17**

1. Download from Oracle archive:
   🔗 [https://www.oracle.com/java/technologies/javase/jdk11-archive-downloads.html](https://www.oracle.com/java/technologies/javase/jdk11-archive-downloads.html)

2. Install Java JDK by running the downloaded `.exe` file.

3. **Set Environment Variables**:

   * Open `System Properties > Environment Variables`.
   * Under **System variables**:

     * Add or update:

       * `JAVA_HOME = C:\Program Files\Java\jdk-17`
       * Append `%JAVA_HOME%\bin` to the `Path` variable.
   * Open CMD and verify:

     ```bash
     java -version
     javac -version
     ```

---

## **Step 2: Set Up SonarQube**

### A. Download and Extract

1. Download **SonarQube Community Edition**:
   🔗 [https://www.sonarsource.com/products/sonarqube/downloads/](https://www.sonarsource.com/products/sonarqube/downloads/)

2. Download **SonarQube Scanner CLI**:
   🔗 [https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-5.0.1.3006-windows.zip](https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-5.0.1.3006-windows.zip)

3. Create a folder `C:\SonarQube\`, and extract **both ZIPs** there:

   * `C:\SonarQube\sonarqube-...`
   * `C:\SonarQube\sonar-scanner-...`

---

### B. Start SonarQube Server

1. Open CMD **as Administrator**.

2. Go to `bin/windows-x86-xx` inside the `sonarqube` folder:

   ```bash
   cd C:\SonarQube\sonarqube-*\bin\windows-x86-xx
   StartSonar.bat
   ```

3. Open browser:
   🔗 [http://localhost:9000](http://localhost:9000)

4. Login:

   * Username: `admin`
   * Password: `admin` → Then change password when prompted.

---

### C. Generate SonarQube Token

1. Go to `My Account > Security`.
2. In **Generate Tokens**, enter a name (e.g., `UserToken`) and click **Generate**.
3. Copy the token (you won’t see it again).

---

## **Step 3: Install Jenkins**

### A. Download & Install

1. Download Jenkins from:
   🔗 [https://www.jenkins.io/download/](https://www.jenkins.io/download/)

2. Install it normally. In the setup wizard:

   * Set Jenkins to **Run as LocalSystem**
   * Jenkins will start at:
     🔗 [http://localhost:8080](http://localhost:8080)

3. Find initial password:

   ```plaintext
   C:\Program Files\Jenkins\secrets\initialAdminPassword
   ```

4. Enter the password in browser when prompted.

5. Choose **Install Suggested Plugins**.

6. Create admin user (or continue with default).

---

### B. Configure SonarQube in Jenkins

1. Jenkins → **Manage Jenkins** → **Manage Plugins** → **Available** tab.
2. Search and install **SonarQube Scanner for Jenkins**, then restart Jenkins.

---

### C. Connect Jenkins to SonarQube

1. Jenkins → **Manage Jenkins** → **Configure System**.
2. Scroll to **SonarQube servers**:

   * Name: `SonarQube`
   * Server URL: `http://localhost:9000`
   * Server Authentication Token:

     * Add credentials → Kind: `Secret Text`
     * Secret: paste your generated **SonarQube token**
     * ID: `sonartoken`, Description: `SQ token`
   * Check **Enable injection of SonarQube server configuration as build environment variables**

---

### D. Add Sonar Scanner Tool

1. Jenkins → **Manage Jenkins** → **Global Tool Configuration**.
2. Under **SonarQube Scanner**:

   * Name: `sonar-scanner`
   * Manually install → Set `Path to executable` as:

     ```
     C:\SonarQube\sonar-scanner-*/bin
     ```

---

## **Step 4: Create Java Project with Sonar Configuration**

### A. Create Folder: `My-java-project`

Structure:

```
My-java-project/
│
├── sonar-project.properties
├── pom.xml
└── src/
    └── main/
        └── java/
            └── com/
                └── example/
                    └── App.java
```

---

### `sonar-project.properties`

```properties
sonar.projectKey=my-java-project
sonar.projectName=My Java Project
sonar.projectVersion=1.0
sonar.sources=src/main/java
sonar.sourceEncoding=UTF-8
```

---

### `App.java`

```java
package main.java.com.example;

public class App {
    public static void main(String[] args) {
        System.out.println("Hello, Sonar!");
    }
}
```

---

### `pom.xml`

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">

    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>my-java-project</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>
    <name>My Java Project</name>

    <properties>
        <maven.compiler.source>1.8</maven.compiler.source>
        <maven.compiler.target>1.8</maven.compiler.target>
    </properties>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
            </plugin>
        </plugins>
    </build>
</project>
```

---

### B. Push Code to GitHub

```bash
git init
git remote add origin <your_repo_url>
git add .
git commit -m "Initial commit"
git branch -M main        # or: git branch -M master
git push -u origin main
```

---

## **Step 5: Jenkins CI/CD Setup**

1. Open Jenkins dashboard → Click **New Item**.

2. Enter item name: `my-java-project` → Select **Freestyle project** → Click **OK**.

3. In **Configuration**:

   * **Source Code Management** → Select **Git**

     * Repository URL: `<your GitHub repo URL>`
     * Branch Specifier: `*/main` or `*/master`
   * **Build Environment** → Select:

     * **Provide Configuration Variables** from SonarQube
   * **Build Steps** → Add **Invoke SonarQube Scanner**

     * Add the following as **Analysis properties**:

       ```
       sonar.projectKey=my-java-project
       sonar.projectName=My Java Project
       sonar.sources=src/main/java
       sonar.projectVersion=1.0
       sonar.sourceEncoding=UTF-8
       ```

4. Click **Save**, then **Build Now**.

5. Check build output in **Console Output**.
