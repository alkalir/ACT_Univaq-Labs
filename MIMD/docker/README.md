# Docker Setup

## Step 1 — Install Docker Desktop

Install [Docker Desktop](https://www.docker.com/products/docker-desktop/) for your OS. Start it and wait until the whale icon in the system tray is stable.

---

## Step 2 — Pull the image

Open a terminal and run:

```bash
docker pull alkalir/mimdlab
```

This is a one-time download (~400 MB). After this you can work offline.

---

## Step 3 — Start the container

When you are ready to compile, open a terminal and run:

**Windows (PowerShell):**
```powershell
docker run -it --rm -v C:\mylab:/lab alkalir/mimdlab
```

**macOS / Linux:**
```bash
docker run -it --rm -v ~/mylab:/lab alkalir/mimdlab
```

The `-v` flag mounts your `mylab` folder into the container at `/lab`. Any file you save in `mylab` from your machine is immediately visible inside the container, and vice versa.

---

## Step 4 — Check your files are there

Inside the container, verify that your working folder is mounted correctly:

```bash
ls /lab
```

You should see the files you saved in `mylab` on your machine.

---

## Exit the container

```bash
exit
```

Your files remain in your `mylab` folder. The container is removed automatically (`--rm`), but the image stays and you can start a new container anytime.

---

You are all set — go back to [README.md](../README.md) and continue from there.
