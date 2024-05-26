# Usa una imagen base de Ubuntu
FROM ubuntu:latest

# Actualiza los paquetes e instala las dependencias necesarias
RUN apt-get update && apt-get install -y \
    g++ \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Copia el código fuente del proyecto al contenedor
COPY . /app

# Establece el directorio de trabajo
WORKDIR /app