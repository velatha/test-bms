# .devfile.yaml - Detailed Documentation

## 📋 Table of Contents

- [Overview](#overview)
- [What is a Devfile?](#what-is-a-devfile)
- [File Structure](#file-structure)
- [Configuration Reference](#configuration-reference)
  - [Schema Version](#schema-version)
  - [Metadata](#metadata)
  - [Components](#components)
  - [Commands](#commands)
  - [Events](#events)
- [Usage Guide](#usage-guide)
- [Command Details](#command-details)
- [Customization](#customization)
- [Troubleshooting](#troubleshooting)
- [Best Practices](#best-practices)
- [Advanced Configuration](#advanced-configuration)
- [References](#references)

## 🔍 Overview

The `.devfile.yaml` file defines the complete development environment configuration for the test-bms project. It specifies:

- Container images to use
- Development tools and dependencies
- Build and test commands
- Startup procedures
- Resource allocations

This configuration enables:
- ✅ **Consistency**: Same environment for all developers
- ✅ **Automation**: Dependencies installed automatically
- ✅ **Portability**: Works in any devfile-compatible platform
- ✅ **Simplicity**: Zero manual setup required

## 📚 What is a Devfile?

A **devfile** is a YAML configuration file that defines a portable development environment. It's part of the [Devfile specification](https://devfile.io/), supported by:

- **Eclipse Che**: Cloud-based IDE
- **OpenShift Dev Spaces**: Red Hat's enterprise developer workspace
- **Podman Desktop**: Container-based development
- **VS Code with extensions**: Local development support

### Key Benefits

1. **Environment as Code**: Development environment is version-controlled
2. **Reproducibility**: Identical setup across machines and teams
3. **Onboarding**: New developers get started in minutes
4. **Cloud-Native**: Works in cloud and local environments
5. **Tool Agnostic**: Not tied to specific IDE or platform

## 🏗️ File Structure

```yaml
schemaVersion: 2.2.0           # Devfile specification version
metadata:                       # Project metadata
  name: test-bms
  version: 1.0.0
components:                     # Container and tool definitions
  - name: nodejs
    container: {...}
commands:                       # Build, run, test commands
  - id: install-system-deps
    exec: {...}
  - id: install
    exec: {...}
  - id: build
    exec: {...}
  - id: type-check
    exec: {...}
events:                         # Lifecycle events
  postStart:
    - install-system-deps
    - install
```

## 📖 Configuration Reference

### Schema Version

```yaml
schemaVersion: 2.2.0
```

**Purpose**: Specifies the devfile specification version being used.

**Details**:
- **Version 2.2.0**: Current stable version
- **Compatibility**: Ensures parsing and behavior consistency
- **Evolution**: Different versions may support different features

**Available Versions**:
- `2.0.0`: Initial stable release
- `2.1.0`: Added new component types
- `2.2.0`: Enhanced command definitions and events (current)

### Metadata

```yaml
metadata:
  name: test-bms
  version: 1.0.0
```

**Fields**:

| Field | Type | Description | Required |
|-------|------|-------------|----------|
| `name` | string | Project identifier | Yes |
| `version` | string | Project version (semantic versioning) | No |
| `displayName` | string | Human-readable project name | No |
| `description` | string | Project description | No |
| `tags` | string[] | Project tags for categorization | No |
| `projectType` | string | Type of project (e.g., "TypeScript") | No |
| `language` | string | Primary programming language | No |

**Example with all fields**:
```yaml
metadata:
  name: test-bms
  version: 1.0.0
  displayName: Test BMS - Fibonacci Generator
  description: TypeScript implementation of Fibonacci sequence generator
  tags:
    - TypeScript
    - Fibonacci
    - Algorithm
  projectType: TypeScript
  language: TypeScript
```

### Components

```yaml
components:
  - name: nodejs
    container:
      image: node:18
      memoryLimit: 1Gi
      sourceMapping: /ramdisk/app/test-bms
```

**Purpose**: Defines the runtime containers and tools used in the development environment.

#### Component: nodejs

| Field | Value | Description |
|-------|-------|-------------|
| `name` | `nodejs` | Component identifier |
| `container.image` | `node:18` | Docker image (Node.js version 18) |
| `container.memoryLimit` | `1Gi` | Maximum memory allocation (1 Gigabyte) |
| `container.sourceMapping` | `/ramdisk/app/test-bms` | Where source code is mounted in container |

#### Container Configuration Details

**Image Selection**:
- **`node:18`**: Official Node.js Docker image
- **Why Node 18?**: 
  - LTS (Long Term Support) release
  - Includes npm package manager
  - Compatible with TypeScript 5.x
  - ES2022 support

**Memory Limit**:
- **`1Gi`**: 1 Gigabyte (1024 Mebibytes)
- **Why 1Gi?**:
  - Sufficient for TypeScript compilation
  - Allows for development tools
  - Not too resource-heavy
  - Can be adjusted based on needs

**Source Mapping**:
- **`/ramdisk/app/test-bms`**: Mount point in container
- **Why ramdisk?**:
  - Faster I/O operations
  - Better performance for compilation
  - Volatile storage (lost on restart)
  - Common pattern in cloud IDEs

#### Additional Container Options

```yaml
# Example with more options
container:
  image: node:18
  memoryLimit: 1Gi
  memoryRequest: 512Mi          # Minimum memory to allocate
  cpuLimit: 2000m               # Max 2 CPU cores
  cpuRequest: 500m              # Min 0.5 CPU core
  sourceMapping: /ramdisk/app/test-bms
  mountSources: true            # Mount source code (default: true)
  env:                          # Environment variables
    - name: NODE_ENV
      value: development
  volumeMounts:                 # Additional volume mounts
    - name: npm-cache
      path: /root/.npm
  endpoints:                    # Expose ports
    - name: app
      targetPort: 3000
      exposure: public
```

### Commands

Commands define executable tasks in the development environment.

#### Command Structure

```yaml
commands:
  - id: command-id              # Unique identifier
    exec:                       # Execution specification
      component: nodejs         # Which component runs this
      commandLine: ...          # Shell command to execute
      workingDir: ...           # Working directory
      group:                    # Command grouping
        kind: build|run|test|debug
        isDefault: true|false   # Default for its group
```

#### Command 1: install-system-deps

```yaml
- id: install-system-deps
  exec:
    component: nodejs
    commandLine: apt-get update && apt-get install -y git findutils grep curl wget
    workingDir: /ramdisk/app/test-bms
    group:
      kind: build
```

**Purpose**: Installs system-level dependencies required for development.

**Details**:
- **When**: Runs automatically on workspace startup (`postStart` event)
- **Component**: Executes in the `nodejs` container
- **Command**: `apt-get update && apt-get install -y git findutils grep curl wget`
  - `apt-get update`: Updates package lists
  - `apt-get install -y`: Installs packages without prompts
  - **Packages**:
    - `git`: Version control system
    - `findutils`: File search utilities (find, xargs)
    - `grep`: Text search utility
    - `curl`: HTTP client for downloads
    - `wget`: File downloader
- **Working Directory**: `/ramdisk/app/test-bms`
- **Group**: `build` - categorized as build-related command

**Why These Packages?**:
- **git**: Essential for version control operations
- **findutils**: Required by many build scripts and tools
- **grep**: Used by development tools for searching
- **curl/wget**: Downloading dependencies or tools

#### Command 2: install

```yaml
- id: install
  exec:
    component: nodejs
    commandLine: npm install -g typescript
    workingDir: /ramdisk/app/test-bms
    group:
      kind: build
      isDefault: true
```

**Purpose**: Installs TypeScript compiler globally.

**Details**:
- **When**: Runs automatically on workspace startup (after `install-system-deps`)
- **Component**: Executes in the `nodejs` container
- **Command**: `npm install -g typescript`
  - `-g`: Global installation
  - Makes `tsc` command available system-wide
- **Group**: `build` (default build command)
- **isDefault**: `true` - This is the default build command

**Why Global Installation?**:
- Makes TypeScript available everywhere in the container
- No need for local node_modules
- Simpler for single-file compilation
- Could alternatively use local installation for projects

#### Command 3: build

```yaml
- id: build
  exec:
    component: nodejs
    commandLine: tsc fibonacci.ts
    workingDir: /ramdisk/app/test-bms
    group:
      kind: build
```

**Purpose**: Compiles TypeScript to JavaScript.

**Details**:
- **When**: Manually triggered by user
- **Command**: `tsc fibonacci.ts`
  - Compiles `fibonacci.ts` to `fibonacci.js`
  - Uses default TypeScript compiler settings
  - Output is in the same directory
- **Output**: `fibonacci.js` file
- **Group**: `build` - build-related command

**TypeScript Compiler Behavior**:
```bash
# Input: fibonacci.ts
# Output: fibonacci.js (ES module)
# Also generates: fibonacci.js.map (if sourceMaps enabled)
```

**Equivalent Manual Commands**:
```bash
# Run from terminal
tsc fibonacci.ts

# Or with specific options
tsc fibonacci.ts --target ES2022 --module ESNext
```

#### Command 4: type-check

```yaml
- id: type-check
  exec:
    component: nodejs
    commandLine: tsc --noEmit fibonacci.ts
    workingDir: /ramdisk/app/test-bms
    group:
      kind: test
      isDefault: true
```

**Purpose**: Performs type checking without generating output files.

**Details**:
- **When**: Manually triggered, or as default test command
- **Command**: `tsc --noEmit fibonacci.ts`
  - `--noEmit`: Don't generate JavaScript files
  - Only checks for type errors
  - Faster than full compilation
- **Group**: `test` (default test command)
- **isDefault**: `true` - Default test command
- **Exit Code**:
  - `0`: No type errors
  - Non-zero: Type errors found

**Use Cases**:
- Quick type validation during development
- CI/CD pipeline validation
- Pre-commit hooks
- IDE integration

**Example Output**:
```bash
# Success (no output)
$ tsc --noEmit fibonacci.ts
# Exit code: 0

# Type error
$ tsc --noEmit fibonacci.ts
fibonacci.ts:10:5 - error TS2322: Type 'string' is not assignable to type 'number'.
# Exit code: 1
```

### Events

```yaml
events:
  postStart:
    - install-system-deps
    - install
```

**Purpose**: Defines lifecycle hooks that run automatically at specific times.

#### Available Event Types

| Event | When It Runs | Use Case |
|-------|--------------|----------|
| `preStart` | Before workspace starts | Pre-initialization tasks |
| `postStart` | After workspace starts | Setup, installations |
| `preStop` | Before workspace stops | Cleanup, save state |
| `postStop` | After workspace stops | Final cleanup |

#### postStart Event

**Behavior**:
- Runs automatically when workspace starts
- Commands execute in sequence
- Must complete before workspace is "ready"
- Failures are logged but don't prevent workspace start

**Command Sequence**:
1. `install-system-deps`: Install system packages
2. `install`: Install TypeScript

**Execution Flow**:
```
Workspace Start
     ↓
postStart Event Triggered
     ↓
[1] install-system-deps
     ↓ (waits for completion)
[2] install
     ↓ (waits for completion)
Workspace Ready
```

**Timing Considerations**:
- Total time: ~30-60 seconds (depending on network)
- User sees "Starting workspace..." during this time
- Progress may be shown in IDE

## 🚀 Usage Guide

### Using in Eclipse Che / OpenShift Dev Spaces

#### 1. Create Workspace from Devfile

**Method A: URL-based**
```
https://your-che-instance.com/dashboard/#/load-factory?url=https://github.com/your-org/test-bms
```

**Method B: Dashboard**
1. Open Che/Dev Spaces dashboard
2. Click "Create Workspace"
3. Select "Import from Git"
4. Enter repository URL
5. Che automatically detects `.devfile.yaml`
6. Click "Create & Open"

#### 2. Workspace Initialization

```
[Starting workspace...]
├── Creating container from node:18 image
├── Mounting source code to /ramdisk/app/test-bms
├── Running postStart events:
│   ├── install-system-deps (updating packages...)
│   └── install (installing TypeScript...)
└── [Workspace Ready]
```

#### 3. Available Commands

**From Command Palette**:
- `Build: install` - Install TypeScript (already run)
- `Build: build` - Compile TypeScript
- `Test: type-check` - Check types

**From Terminal**:
```bash
# Build the project
tsc fibonacci.ts

# Type check
tsc --noEmit fibonacci.ts

# Run the JavaScript (after building)
node fibonacci.js
```

### Using Locally with Podman/Docker

```bash
# 1. Start container with devfile image
podman run -it --rm \
  -v $(pwd):/ramdisk/app/test-bms \
  -w /ramdisk/app/test-bms \
  node:18 \
  bash

# 2. Inside container, run setup commands
apt-get update && apt-get install -y git findutils grep curl wget
npm install -g typescript

# 3. Build and test
tsc fibonacci.ts
tsc --noEmit fibonacci.ts
```

### Continuous Integration

```yaml
# .github/workflows/ci.yml
name: CI
on: [push, pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: 18
      
      - name: Install TypeScript
        run: npm install -g typescript
      
      - name: Type Check
        run: tsc --noEmit fibonacci.ts
      
      - name: Build
        run: tsc fibonacci.ts
```

## 🔧 Command Details

### Running Commands

#### In Eclipse Che / Dev Spaces

**Method 1: Command Palette**
1. Press `F1` or `Ctrl+Shift+P`
2. Type command name (e.g., "build")
3. Select from list
4. Command executes in terminal

**Method 2: Terminal**
```bash
# Just type the command directly
tsc fibonacci.ts
```

**Method 3: Task Runner**
- Some IDEs show tasks in sidebar
- Click to execute
- View output in terminal panel

#### Command Output

**install-system-deps**:
```bash
$ apt-get update && apt-get install -y git findutils grep curl wget
Get:1 http://security.debian.org/debian-security bullseye-security InRelease [48.4 kB]
...
Setting up git (1:2.30.2-1) ...
Setting up findutils (4.8.0-1) ...
...
Done.
```

**install**:
```bash
$ npm install -g typescript
added 1 package, and audited 2 packages in 3s
```

**build**:
```bash
$ tsc fibonacci.ts
# No output if successful
# Creates fibonacci.js
```

**type-check**:
```bash
$ tsc --noEmit fibonacci.ts
# No output if types are correct
# Errors displayed if issues found
```

### Command Exit Codes

| Exit Code | Meaning | Example |
|-----------|---------|---------|
| `0` | Success | Type check passed |
| `1` | Error | Type error found |
| `2` | Fatal error | TypeScript not installed |
| `130` | Interrupted | Ctrl+C pressed |

## 🎨 Customization

### Adding New Commands

```yaml
commands:
  # ... existing commands ...
  
  # Run the compiled JavaScript
  - id: run
    exec:
      component: nodejs
      commandLine: node fibonacci.js
      workingDir: /ramdisk/app/test-bms
      group:
        kind: run
        isDefault: true
  
  # Install project dependencies
  - id: npm-install
    exec:
      component: nodejs
      commandLine: npm install
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
  
  # Format code with Prettier
  - id: format
    exec:
      component: nodejs
      commandLine: npx prettier --write "*.ts"
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
  
  # Lint code with ESLint
  - id: lint
    exec:
      component: nodejs
      commandLine: npx eslint "*.ts"
      workingDir: /ramdisk/app/test-bms
      group:
        kind: test
```

### Modifying Container Configuration

```yaml
components:
  - name: nodejs
    container:
      image: node:18
      memoryLimit: 2Gi              # Increase memory
      cpuLimit: 2000m               # Add CPU limit
      env:                          # Add environment variables
        - name: NODE_ENV
          value: development
        - name: LOG_LEVEL
          value: debug
      mountSources: true
      sourceMapping: /ramdisk/app/test-bms
```

### Adding Additional Components

```yaml
components:
  - name: nodejs
    container:
      # ... existing nodejs config ...
  
  # Add a database for testing
  - name: postgres
    container:
      image: postgres:15
      memoryLimit: 512Mi
      env:
        - name: POSTGRES_PASSWORD
          value: devpassword
        - name: POSTGRES_DB
          value: testdb
      endpoints:
        - name: postgres
          targetPort: 5432
  
  # Add Redis cache
  - name: redis
    container:
      image: redis:7
      memoryLimit: 256Mi
      endpoints:
        - name: redis
          targetPort: 6379
```

### Custom Events

```yaml
events:
  postStart:
    - install-system-deps
    - install
    - setup-git                    # Custom setup command
  
  preStop:
    - cleanup                      # Run before stopping workspace

commands:
  # ... existing commands ...
  
  - id: setup-git
    exec:
      component: nodejs
      commandLine: |
        git config --global user.name "Dev User"
        git config --global user.email "dev@example.com"
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
  
  - id: cleanup
    exec:
      component: nodejs
      commandLine: |
        echo "Cleaning up..."
        rm -rf node_modules .cache
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
```

## 🐛 Troubleshooting

### Common Issues

#### 1. TypeScript Not Found

**Symptom**:
```bash
$ tsc fibonacci.ts
bash: tsc: command not found
```

**Solution**:
```bash
# Manually install TypeScript
npm install -g typescript

# Or reinstall via devfile command
# Check if install command ran successfully
```

**Prevention**: Ensure `install` command completed successfully during `postStart`

#### 2. Permission Denied

**Symptom**:
```bash
$ apt-get install git
E: Could not open lock file /var/lib/dpkg/lock - open (13: Permission denied)
```

**Solution**:
- Container may not have root access
- Modify devfile to use rootless container
- Or use images with tools pre-installed

```yaml
components:
  - name: nodejs
    container:
      image: node:18
      memoryRequest: 512Mi
      memoryLimit: 1Gi
      user: root                    # Add this line
```

#### 3. Out of Memory

**Symptom**:
```bash
# Workspace crashes or becomes unresponsive
# Compilation fails with OOM errors
```

**Solution**:
```yaml
components:
  - name: nodejs
    container:
      memoryLimit: 2Gi              # Increase from 1Gi
```

#### 4. Source Code Not Found

**Symptom**:
```bash
$ ls /ramdisk/app/test-bms
# No files shown
```

**Solution**:
- Check `sourceMapping` path matches
- Ensure `mountSources: true` (default)
- Verify repository was cloned correctly

#### 5. Commands Not Appearing

**Symptom**: Commands don't show in IDE command palette

**Solution**:
- Restart workspace
- Check devfile YAML syntax
- Ensure proper indentation
- Validate against devfile schema

### Debug Mode

**Enable verbose logging**:
```yaml
commands:
  - id: build-debug
    exec:
      component: nodejs
      commandLine: tsc --listFiles --traceResolution fibonacci.ts
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
```

**Check environment**:
```yaml
commands:
  - id: debug-env
    exec:
      component: nodejs
      commandLine: |
        echo "=== Environment Info ==="
        echo "Node version: $(node --version)"
        echo "npm version: $(npm --version)"
        echo "TypeScript version: $(tsc --version)"
        echo "Working directory: $(pwd)"
        echo "Files: $(ls -la)"
        echo "Memory: $(free -h)"
      workingDir: /ramdisk/app/test-bms
      group:
        kind: test
```

### Validation

**Validate devfile syntax**:
```bash
# Install devfile validator
npm install -g @devfile/api

# Validate your devfile
devfile-validator .devfile.yaml
```

**Online validation**:
- [Devfile Validator](https://devfile.io/validator/)
- Paste your devfile.yaml content
- Get syntax and structure validation

## ✅ Best Practices

### 1. Resource Management

```yaml
# Good: Specify reasonable limits
components:
  - name: nodejs
    container:
      image: node:18
      memoryRequest: 512Mi          # Minimum needed
      memoryLimit: 2Gi              # Maximum allowed
      cpuRequest: 250m              # 0.25 CPU cores minimum
      cpuLimit: 1000m               # 1 CPU core maximum
```

### 2. Command Organization

```yaml
# Good: Organize commands by purpose
commands:
  # Build commands
  - id: install
    group: {kind: build, isDefault: true}
  - id: build
    group: {kind: build}
  
  # Test commands
  - id: type-check
    group: {kind: test, isDefault: true}
  - id: unit-test
    group: {kind: test}
  
  # Run commands
  - id: run
    group: {kind: run, isDefault: true}
```

### 3. Idempotent Setup

```yaml
# Good: Commands can be run multiple times safely
commands:
  - id: install
    exec:
      commandLine: |
        # Check if TypeScript is already installed
        if ! command -v tsc &> /dev/null; then
          npm install -g typescript
        fi
```

### 4. Fast Startup

```yaml
# Good: Only essential commands in postStart
events:
  postStart:
    - install-essential-deps      # Quick, critical only
    
# Bad: Too many commands slow down startup
events:
  postStart:
    - install-deps
    - install-all-tools
    - run-full-build
    - run-all-tests              # Don't do this!
```

### 5. Clear Command Names

```yaml
# Good: Descriptive, clear names
commands:
  - id: type-check
  - id: build-typescript
  - id: run-dev-server

# Bad: Vague names
commands:
  - id: cmd1
  - id: do-stuff
  - id: x
```

### 6. Documentation

```yaml
metadata:
  name: test-bms
  version: 1.0.0
  description: TypeScript Fibonacci generator with comprehensive documentation
  
# Add comments in YAML
commands:
  - id: build
    # Compiles TypeScript source files to JavaScript
    # Output: fibonacci.js
    exec:
      component: nodejs
      commandLine: tsc fibonacci.ts
```

### 7. Environment Variables

```yaml
# Good: Use env vars for configuration
components:
  - name: nodejs
    container:
      image: node:18
      env:
        - name: NODE_ENV
          value: development
        - name: LOG_LEVEL
          value: info

commands:
  - id: build
    exec:
      commandLine: |
        echo "Building in $NODE_ENV mode..."
        tsc fibonacci.ts
```

## 🚀 Advanced Configuration

### Multi-Container Setup

```yaml
schemaVersion: 2.2.0
metadata:
  name: test-bms-advanced
  version: 1.0.0

components:
  # Main development container
  - name: nodejs
    container:
      image: node:18
      memoryLimit: 2Gi
      sourceMapping: /ramdisk/app/test-bms
      endpoints:
        - name: app
          targetPort: 3000
          exposure: public
  
  # Testing container with different Node version
  - name: nodejs-lts
    container:
      image: node:20
      memoryLimit: 1Gi
      sourceMapping: /ramdisk/app/test-bms
  
  # Database for integration tests
  - name: database
    container:
      image: postgres:15
      memoryLimit: 512Mi
      env:
        - name: POSTGRES_PASSWORD
          value: testpass
      endpoints:
        - name: postgres
          targetPort: 5432

commands:
  - id: test-node-18
    exec:
      component: nodejs
      commandLine: tsc fibonacci.ts && node fibonacci.js
  
  - id: test-node-20
    exec:
      component: nodejs-lts
      commandLine: tsc fibonacci.ts && node fibonacci.js
```

### Volume Mounts

```yaml
components:
  - name: nodejs
    container:
      image: node:18
      memoryLimit: 1Gi
      sourceMapping: /ramdisk/app/test-bms
      volumeMounts:
        - name: npm-cache
          path: /root/.npm
        - name: typescript-cache
          path: /root/.tscache

  # Define volumes
  - name: npm-cache
    volume:
      size: 1Gi
  
  - name: typescript-cache
    volume:
      size: 512Mi
```

### Composite Commands

```yaml
commands:
  # Individual commands
  - id: clean
    exec:
      component: nodejs
      commandLine: rm -rf *.js *.js.map
  
  - id: type-check
    exec:
      component: nodejs
      commandLine: tsc --noEmit fibonacci.ts
  
  - id: build
    exec:
      component: nodejs
      commandLine: tsc fibonacci.ts
  
  # Composite command runs multiple commands in sequence
  - id: full-build
    composite:
      commands:
        - clean
        - type-check
        - build
      parallel: false              # Run sequentially
```

### Conditional Execution

```yaml
commands:
  - id: smart-install
    exec:
      component: nodejs
      commandLine: |
        # Only install if not already present
        if [ ! -f "node_modules/.bin/tsc" ]; then
          echo "Installing TypeScript..."
          npm install -g typescript
        else
          echo "TypeScript already installed"
        fi
        
        # Check versions
        echo "Node: $(node --version)"
        echo "npm: $(npm --version)"
        echo "TypeScript: $(tsc --version)"
      workingDir: /ramdisk/app/test-bms
      group:
        kind: build
```

## 📚 References

### Official Documentation

- **Devfile Specification**: https://devfile.io/
- **Devfile Schema**: https://devfile.io/docs/2.2.0/
- **Eclipse Che**: https://www.eclipse.org/che/docs/
- **OpenShift Dev Spaces**: https://docs.redhat.com/en/documentation/red_hat_openshift_dev_spaces/

### Related Technologies

- **Node.js**: https://nodejs.org/docs/
- **TypeScript**: https://www.typescriptlang.org/docs/
- **npm**: https://docs.npmjs.com/
- **Docker**: https://docs.docker.com/
- **Kubernetes**: https://kubernetes.io/docs/

### Examples and Templates

- **Devfile Registry**: https://registry.devfile.io/
- **Sample Devfiles**: https://github.com/devfile/registry
- **TypeScript Devfile**: https://github.com/devfile-samples/devfile-sample-typescript

### Tools

- **Devfile Validator**: https://www.npmjs.com/package/@devfile/api
- **VS Code Devfile Extension**: https://marketplace.visualstudio.com/items?itemName=redhat.vscode-devfile
- **Podman Desktop**: https://podman-desktop.io/

---

## 📝 Summary

The `.devfile.yaml` configuration provides:

- ✅ **Automated Setup**: Zero-configuration development environment
- ✅ **Consistency**: Same setup across all team members
- ✅ **Portability**: Works on any devfile-compatible platform
- ✅ **Efficiency**: Pre-configured build and test commands
- ✅ **Scalability**: Easy to extend with new tools and commands

### Quick Reference Card

| Task | Command | Location |
|------|---------|----------|
| Install TypeScript | `npm install -g typescript` | Auto-run on startup |
| Build | `tsc fibonacci.ts` | Manual or via IDE |
| Type Check | `tsc --noEmit fibonacci.ts` | Default test command |
| View Logs | Check IDE terminal | During execution |
| Edit Config | Modify `.devfile.yaml` | Restart workspace to apply |

For the main project documentation, see [README.md](../README.md).

For detailed TypeScript code documentation, see [FIBONACCI.md](./FIBONACCI.md).
