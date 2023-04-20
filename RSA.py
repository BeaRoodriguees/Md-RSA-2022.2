import customtkinter
import os
import subprocess
from tkinter import filedialog
from PIL import Image, ImageFont, ImageDraw
import platform
import emoji



class App(customtkinter.CTk):
    def __init__(self, os_name):
        super().__init__()

        self.os_name = os_name

        if(os_name=="Windows"):
            self.files_extension = ".exe"
        else:
            self.files_extension = ""
    
        self.title("Algoritmo de RSA - Matemática Discreta -  UFAL 2022.2")
        self.geometry("1100x580")

        # set grid layout 1x2
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=1)

        # load images with light and dark mode image
        image_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "img")
        self.logo_image = customtkinter.CTkImage(Image.open(os.path.join(image_path, "ufal.png")), size=(36, 56))
        self.smile = customtkinter.CTkImage(Image.open(os.path.join(image_path, "smile.png")), size=(15, 15))
        self.heart = customtkinter.CTkImage(Image.open(os.path.join(image_path, "heart.png")), size=(15, 15))
        self.home_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "home_dark.png")),
                                                dark_image=Image.open(os.path.join(image_path, "home_light.png")), size=(30, 30))
        self.key_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "key_dark.png")),
                                                dark_image=Image.open(os.path.join(image_path, "key_light.png")), size=(30, 30))
        self.encrypt_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "encrypt_dark.png")),
                                                    dark_image=Image.open(os.path.join(image_path, "encrypt_light.png")), size=(30, 30))
        self.decrypt_image = customtkinter.CTkImage(light_image=Image.open(os.path.join(image_path, "decrypt_dark.png")),
                                                    dark_image=Image.open(os.path.join(image_path, "decrypt_light.png")), size=(30, 30))

        # create navigation frame
        self.navigation_frame = customtkinter.CTkFrame(self, corner_radius=0)
        self.navigation_frame.grid(row=0, column=0, sticky="nsew")
        self.navigation_frame.grid_rowconfigure(5, weight=1)

        self.navigation_frame_label = customtkinter.CTkLabel(self.navigation_frame, text="  Equipe Advanced", image=self.logo_image,
                                                             compound="left", font=customtkinter.CTkFont(size=15, weight="bold"))
        self.navigation_frame_label.grid(row=0, column=0, padx=20, pady=20)

        self.home_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Início",
                                                   fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                   image=self.home_image, anchor="w", command=self.home_button_event)
        self.home_button.grid(row=1, column=0, sticky="ew")

        self.frame_2_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Gerar Chave Pública",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      image=self.key_image, anchor="w", command=self.frame_2_button_event)
        self.frame_2_button.grid(row=2, column=0, sticky="ew")

        self.frame_3_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Criptografar Texto",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      image=self.encrypt_image, anchor="w", command=self.frame_3_button_event)
        self.frame_3_button.grid(row=3, column=0, sticky="ew")

        self.frame_4_button = customtkinter.CTkButton(self.navigation_frame, corner_radius=0, height=40, border_spacing=10, text="Descriptografar Texto",
                                                      fg_color="transparent", text_color=("gray10", "gray90"), hover_color=("gray70", "gray30"),
                                                      image=self.decrypt_image, anchor="w", command=self.frame_4_button_event)
        self.frame_4_button.grid(row=4, column=0, sticky="ew")

        self.appearance_mode_label = customtkinter.CTkLabel(self.navigation_frame, text="Tema:", font=customtkinter.CTkFont(size=15))
        self.appearance_mode_label.grid(row=5, column=0, padx=(0,0), pady=(20,0), sticky="s")

        self.appearance_mode_menu = customtkinter.CTkOptionMenu(self.navigation_frame, values=["System", "Dark","Light"],
                                                                command=self.change_appearance_mode_event)
        self.appearance_mode_menu.grid(row=6, column=0, padx=0, pady=(0,20), sticky="s")

        # create home frame
        self.home_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.home_frame.grid_columnconfigure(0, weight=1)
        self.home_frame_label = customtkinter.CTkLabel(self.home_frame, text="Bem-Vindo!\n Para Iniciar, Selecione uma opção ao lado.",
                                                             compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.home_frame_label.grid(row=0, column=0, padx=0, pady=60)
        self.home_frame_label2 = customtkinter.CTkLabel(self.home_frame, text="Projeto Desenvolvido por:\n Arthur Pontes de Miranda Ramos Soares\nBeatriz Rodrigues Cavalcante\nDavi Da Silva Romao\nFelipe Lira Da Silva\nGabriel Gomes De Oliveira\n\n Professor: Bruno Pimentel\n Disciplina: Matemática Discreta",
                                                             compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.home_frame_label2.grid(row=1, column=0, padx=0, pady=40)
        self.home_frame_label1 = customtkinter.CTkLabel(self.home_frame, text="Algoritmo RSA desenvolvido em C.\nInteface desenvolvida em Python.",
                                                             compound="center", font=customtkinter.CTkFont(size=14, weight="bold"))
        self.home_frame_label1.grid(row=2, column=0, padx=(0,20), pady=100)
        self.home_frame_label1 = customtkinter.CTkLabel(self.home_frame, text="", image=self.smile,
                                                             compound="center", font=customtkinter.CTkFont(size=14, weight="bold"))
        self.home_frame_label1.grid(row=2, column=0, padx=(280,25), pady=(69,90))
        self.home_frame_label1 = customtkinter.CTkLabel(self.home_frame, text="", image=self.heart,
                                                             compound="center", font=customtkinter.CTkFont(size=14, weight="bold"))
        self.home_frame_label1.grid(row=2, column=0, padx=(280,31), pady=(100,82))

        # create second frame
        self.second_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.second_frame.grid_columnconfigure(0, weight=1)
          # create main entry and button
        self.second_frame_label = customtkinter.CTkLabel(self.second_frame, text="Gerar Chave Pública\n Digite os valores de P, Q , E e confirme.",
                                                             compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.second_frame_label.grid(row=0, column=0, padx=20, pady=120)
        self.entry1 = customtkinter.CTkEntry(self.second_frame, placeholder_text="Insira o valor de P...")
        self.entry1.grid(row=2, column=0, columnspan=1,  padx=(0, 450), pady=(0, 0), sticky="")
        self.entry2 = customtkinter.CTkEntry(self.second_frame, placeholder_text="Insira o valor de Q...")
        self.entry2.grid(row=2, column=0, columnspan=2, padx=(0, 0), pady=(0, 0), sticky="")
        self.entry3 = customtkinter.CTkEntry(self.second_frame, placeholder_text="Insira o valor de E...")
        self.entry3.grid(row=2, column=0, columnspan=3, padx=(450, 0), pady=(0, 0), sticky="")
        self.second_frame_button_1 = customtkinter.CTkButton(self.second_frame, text="Gerar", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.genPbKey)
        self.second_frame_button_1.grid(row=3, column=0, padx=0, pady=70)
        self.second_frame_label3 = customtkinter.CTkLabel(self.second_frame, text="status:",
                                                             compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.second_frame_label3.grid(row=4, column=0, padx=20, pady=10)

        # create third frame
        self.third_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.third_frame.grid_columnconfigure(0, weight=1)

        self.third_frame_label = customtkinter.CTkLabel(self.third_frame, text="Criptografar Texto\n Digite ou importe o texto a ser criptografado e a chave pública.", 
                                                            compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.third_frame_label.grid(row=0, column=0, padx=0, pady=(15, 10))

        self.crypto_text = customtkinter.CTkTextbox(self.third_frame, height=300, width=700)
        self.crypto_text.grid(row=1, column=0, padx=0, pady=(5, 10))
        self.status1 = customtkinter.CTkLabel(self.third_frame, text="Status: ", compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.status1.grid(row=2, column=0, padx=0, pady=(0, 20))
        self.entry4 = customtkinter.CTkEntry(self.third_frame, placeholder_text="Insira o valor de N...")
        self.entry4.grid(row=3, column=0, columnspan=3, padx=(0, 225), pady=(0, 0), sticky="")
        self.entry5 = customtkinter.CTkEntry(self.third_frame, placeholder_text="Insira o valor de E...")
        self.entry5.grid(row=3, column=0, columnspan=3, padx=(225, 0), pady=(0, 0), sticky="")
        self.btnImport1 = customtkinter.CTkButton(self.third_frame, text="  Importar  Mensagem  ", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.loadMsg1)
        self.btnImport1.grid(row=4, column=0, padx=(0, 225), pady=(15, 15))
        self.btnImport2 = customtkinter.CTkButton(self.third_frame, text="Importar Chave Pública", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.loadPbKey)
        self.btnImport2.grid(row=4, column=0, padx=(225, 0), pady=(15, 15))
        self.btnEncrypt = customtkinter.CTkButton(self.third_frame, text="Encriptar", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.encryptMsg)
        self.btnEncrypt.grid(row=5, column=0, padx=0, pady=0)
        # create des frame
        self.des_frame = customtkinter.CTkFrame(self, corner_radius=0, fg_color="transparent")
        self.des_frame.grid_columnconfigure(0, weight=1)
        self.des_frame_label = customtkinter.CTkLabel(self.des_frame, text="Descriptografar Texto\n Digite ou importe o texto a ser descriptografado e a chave privada.",
                                                                compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.des_frame_label.grid(row=0, column=0, padx=0, pady=(15, 10))
        self.des_text = customtkinter.CTkTextbox(self.des_frame, height=300, width=700, )
        self.des_text.grid(row=1, column=0, padx=0, pady=(5, 10))
        self.status2 = customtkinter.CTkLabel(self.des_frame, text="Status: ", compound="center", font=customtkinter.CTkFont(size=18, weight="bold"))
        self.status2.grid(row=2, column=0, padx=0, pady=(0, 20))
        self.entry6 = customtkinter.CTkEntry(self.des_frame, placeholder_text="Insira o valor de P...")
        self.entry6.grid(row=3, column=0, columnspan=3, padx=(0, 350), pady=(0, 0), sticky="")
        self.entry7 = customtkinter.CTkEntry(self.des_frame, placeholder_text="Insira o valor de Q...")
        self.entry7.grid(row=3, column=0, columnspan=3, padx=(0, 0), pady=(0, 0), sticky="")
        self.entry8 = customtkinter.CTkEntry(self.des_frame, placeholder_text="Insira o valor de E...")
        self.entry8.grid(row=3, column=0, columnspan=3, padx=(350, 0), pady=(0, 0), sticky="")
        self.btnImport3 = customtkinter.CTkButton(self.des_frame, text="  Importar  Mensagem  ", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.loadMsg2)
        self.btnImport3.grid(row=4, column=0, padx=(0, 225), pady=(15, 15))
        self.btnImport4 = customtkinter.CTkButton(self.des_frame, text="Importar Chave Privada", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.loadPvKey)
        self.btnImport4.grid(row=4, column=0, padx=(225, 0), pady=(15, 15))
        self.btnDecrypt = customtkinter.CTkButton(self.des_frame, text="Descriptografar", compound="top",font=customtkinter.CTkFont(size=15, weight="bold",),command=self.decryptMsg)
        self.btnDecrypt.grid(row=5, column=0, padx=0, pady=0)

        # select default frame
        self.select_frame_by_name("Início")

    def select_frame_by_name(self, name):
        # set button color for selected button
        self.home_button.configure(fg_color=("gray75", "gray25") if name == "Início" else "transparent")
        self.frame_2_button.configure(fg_color=("gray75", "gray25") if name == "Gerar Chave Pública" else "transparent")
        self.frame_3_button.configure(fg_color=("gray75", "gray25") if name == "Criptografar Texto" else "transparent")
        self.frame_4_button.configure(fg_color=("gray75", "gray25") if name == "Descriptografar Texto" else "transparent")

        # show selected frame
        if name == "Início":
            self.home_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.home_frame.grid_forget()
        if name == "Gerar Chave Pública":
            self.second_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.second_frame.grid_forget()
        if name == "Criptografar Texto":
            self.third_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.third_frame.grid_forget()
        if name == "Descriptografar Texto":
            self.des_frame.grid(row=0, column=1, sticky="nsew")
        else:
            self.des_frame.grid_forget()

    def home_button_event(self):
        self.select_frame_by_name("Início")

    def frame_2_button_event(self):
        self.select_frame_by_name("Gerar Chave Pública")

    def frame_3_button_event(self):
        self.select_frame_by_name("Criptografar Texto")
    
    def frame_4_button_event(self):
        self.select_frame_by_name("Descriptografar Texto")

    def loadMsg1(self):
        self.arquivo = filedialog.askopenfilename(initialdir="/", title="Selecione o arquivo", filetypes=(("txt files", "*.txt"), ("all files", "*.*")))
        with open(self.arquivo, 'r') as f:
            self.texto = f.read()
            self.crypto_text.insert("0.0", text=self.texto)
    
    def loadMsg2(self):
        self.arquivo = filedialog.askopenfilename(initialdir="/", title="Selecione o arquivo", filetypes=(("txt files", "*.txt"), ("all files", "*.*")))
        with open(self.arquivo, 'r') as f:
            self.texto = f.read()
            self.des_text.insert("0.0", text=self.texto)

    def loadPbKey(self):
        self.arquivo = filedialog.askopenfilename(initialdir="/", title="Selecione o arquivo", filetypes=(("txt files", "*.txt"), ("all files", "*.*")))
        with open(self.arquivo, 'r') as f:
            self.texto = f.read()
            self.texto = self.texto.split(" ")
            self.entry4.insert(0, self.texto[0])
            self.entry5.insert(0, self.texto[1])

    def loadPvKey(self):
        self.arquivo = filedialog.askopenfilename(initialdir="/", title="Selecione o arquivo", filetypes=(("txt files", "*.txt"), ("all files", "*.*")))
        with open(self.arquivo, 'r') as f:
            self.texto = f.read()
            self.texto = self.texto.split(" ")
            self.entry6.insert(0, self.texto[0])
            self.entry7.insert(0, self.texto[1])
            self.entry8.insert(0, self.texto[2])

    def genPbKey(self):
        file = open('pqekey.txt', 'w')
        file.write(str(self.entry1.get())+" "+str(self.entry2.get())+" "+str(self.entry3.get()))
        file.close()
        line = ""
        cmd = './bin/genPublicKey' + self.files_extension

        if(self.os_name=="Windows"):
            process = subprocess.Popen('powershell.exe '+ cmd, shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
            line = process.stdout.read().decode('utf-8').rstrip()
        else:
            process = subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE)    
            line = process.stdout.decode('utf-8').rstrip()
        errcode = process.returncode
        self.second_frame_label3.configure(text=line)

    def encryptMsg(self):
        file = open('publickey.txt', 'w')
        file.write(str(self.entry4.get())+" "+str(self.entry5.get()))
        file.close()
        file = open('mensagem.txt', 'w')
        file.write(str(self.crypto_text.get("0.0", "end-1c")))
        file.close()

        line = ""
        cmd = './bin/encrypt' + self.files_extension
        
        if(self.os_name=="Windows"):
            process = subprocess.Popen('powershell.exe '+ cmd, shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
            line = process.stdout.read().decode('utf-8').rstrip()
        else:
            process = subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE)    
            line = process.stdout.decode('utf-8').rstrip()
        errcode = process.returncode
        self.status1.configure(text=line)
        with open('mensagem_encriptada.txt','r') as msg:
            msgEncrypt = msg.read()
            self.crypto_text.delete("0.0", "end")
            self.crypto_text.insert("0.0", text=msgEncrypt)
            msg.close()

    def decryptMsg(self):
        file = open('pqekey.txt', 'w')
        file.write(str(self.entry6.get())+" "+str(self.entry7.get()) + " " + str(self.entry8.get()))
        file.close()
        file = open('mensagem_encriptada.txt', 'w')
        file.write(str(self.des_text.get("0.0", "end-1c")))
        file.close()

        line = ""
        cmd = './bin/decrypt' + self.files_extension
    
        if(self.os_name=="Windows"):
            process = subprocess.Popen('powershell.exe '+ cmd, shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
            line = process.stdout.read().decode('utf-8').rstrip()
        else:
            process = subprocess.run([cmd], stdout=subprocess.PIPE, stderr=subprocess.PIPE)    
            line = process.stdout.decode('utf-8').rstrip()
        errcode = process.returncode
        self.status2.configure(text=line)
        with open('mensagem_desencriptada.txt','r') as msg:
            msgDecrypt = msg.read()
            self.des_text.delete("0.0", "end")
            self.des_text.insert("0.0", text=msgDecrypt)
            msg.close()


    def change_appearance_mode_event(self, new_appearance_mode):
        customtkinter.set_appearance_mode(new_appearance_mode)

    
def compile_archives(os_name):
    extension_name = ""

    if(os_name=="Windows"):
        extension_name=".exe"

    subprocess.run(["gcc", "decrypt.c", "-o", "./bin/decrypt"+extension_name, "-lgmp"])
    subprocess.run(["gcc", "encrypt.c", "-o", "./bin/encrypt"+extension_name, "-lgmp"])
    subprocess.run(["gcc", "genPublicKey.c", "-o", "./bin/genPublicKey"+extension_name, "-lgmp"])

        
    

if __name__ == "__main__":
    os_name = platform.system()
    compile_archives(os_name)
    app = App(os_name)
    app.mainloop()