### 🔧 1. Prerequisite: Create the Maven-based project

* Create the Maven-based project as given previously:

  ```bash
  mvn archetype:generate -DgroupId=com.example -DartifactId=demo-project -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false
  cd demo-project
  ```

---

### 2. Delete `pom.xml`

```bash
del pom.xml  # On Windows
# OR
rm pom.xml   # On Linux/Mac
```

---

### 3. Install Gradle (if not already installed)

* Download **Gradle binary-only ZIP** from:
  [https://gradle.org/releases/](https://gradle.org/releases/)

* Extract and set the `GRADLE_HOME` system environment variable
  Add `GRADLE_HOME/bin` to `PATH`.

---

### 4. Verify Gradle Installation

```bash
gradle -v
```

---

### 5. Add the following files in `demo-project/` folder:

---

#### `build.gradle`

```groovy
plugins {
    id 'java'
}

group = 'com.example'
version = '1.0-SNAPSHOT'

repositories {
    mavenCentral()
}

java {
    sourceCompatibility = JavaVersion.VERSION_17
    targetCompatibility = JavaVersion.VERSION_17
}

dependencies {
    testImplementation 'junit:junit:4.13.2'
}
```

---

#### `settings.gradle`

```groovy
rootProject.name = 'demo-project'
```

---

### 6. Build, Test, and Run the Project

```bash
cd demo-project

# Build project (compiles + packages .jar)
gradle build

# Run tests
gradle test

# Run the app
java -cp build/libs/demo-project-1.0-SNAPSHOT.jar com.example.App
```

---

### Output

You should see:

```
Hello World!
```
