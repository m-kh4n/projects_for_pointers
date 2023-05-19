# MENTAL WARD DATABASE
# A MINI PROJECT BY: m_kh4n

import sqlite3
from tkinter import *
from tkinter import messagebox

# Establish a connection to the database
conn = sqlite3.connect("patients.db")
cursor = conn.cursor()

# Create the patient table if it doesn't exist
cursor.execute("CREATE TABLE IF NOT EXISTS patients (id INTEGER PRIMARY KEY, name TEXT, age INTEGER, illness TEXT)")

# Create the prescriptions table if it doesn't exist
cursor.execute("CREATE TABLE IF NOT EXISTS prescriptions (illness TEXT PRIMARY KEY, drug TEXT)")

# Function to open the patient records window
def open_patient_records_window():
    patient_records_window = Toplevel(root)
    patient_records_window.title("Patient Records")

    # Function to insert a new patient
    def insert_patient():
        name = name_entry.get()
        age = age_entry.get()
        illness = illness_entry.get()
        cursor.execute("INSERT INTO patients (name, age, illness) VALUES (?, ?, ?)", (name, age, illness))
        conn.commit()
        status_label["text"] = "Patient inserted successfully."

    # Function to search for a patient
    def search_patient():
        name = name_entry.get()
        cursor.execute("SELECT * FROM patients WHERE name=?", (name,))
        result = cursor.fetchall()
        if result:
            status_label["text"] = f"Found {len(result)} patient(s)."
        else:
            status_label["text"] = "Patient not found."

    # Function to delete a patient
    def delete_patient():
        name = name_entry.get()
        cursor.execute("DELETE FROM patients WHERE name=?", (name,))
        conn.commit()
        status_label["text"] = "Patient deleted successfully."

    # Function to update a patient's age
    def update_patient():
        name = name_entry.get()
        age = age_entry.get()
        cursor.execute("UPDATE patients SET age=? WHERE name=?", (age, name))
        conn.commit()
        status_label["text"] = "Patient updated successfully."

    # Function to display the entire patient database
    def display_patient_database():
        cursor.execute("SELECT * FROM patients")
        result = cursor.fetchall()
        if result:
            messagebox.showinfo("Patient Database", "\n".join(str(row) for row in result))
        else:
            messagebox.showinfo("Patient Database", "No patients found.")

    name_label = Label(patient_records_window, text="Name:")
    name_label.pack()
    name_entry = Entry(patient_records_window)
    name_entry.pack()

    age_label = Label(patient_records_window, text="Age:")
    age_label.pack()
    age_entry = Entry(patient_records_window)
    age_entry.pack()

    illness_label = Label(patient_records_window, text="Illness:")
    illness_label.pack()
    illness_entry = Entry(patient_records_window)
    illness_entry.pack()

    insert_button = Button(patient_records_window, text="Insert", command=insert_patient)
    insert_button.pack()

    search_button = Button(patient_records_window, text="Search", command=search_patient)
    search_button.pack()

    update_button = Button(patient_records_window, text="Update", command=update_patient)
    update_button.pack()

    delete_button = Button(patient_records_window, text="Delete", command=delete_patient)
    delete_button.pack()

    display_button = Button(patient_records_window, text="Display Database", command=display_patient_database)
    display_button.pack()

    status_label = Label(patient_records_window, text="")
    status_label.pack()

# Function to open the illness table window
def open_illness_table_window():
    illness_table_window = Toplevel(root)
    illness_table_window.title("Illness Table")

    # Function to insert a new illness and corresponding drug
    def insert_illness():
        illness = illness_entry.get()
        drug = drug_entry.get()
        cursor.execute("INSERT INTO prescriptions (illness, drug) VALUES (?, ?)", (illness, drug))
        conn.commit()
        status_label["text"] = "Prescription inserted successfully."

    # Function to search for an illness
    def search_illness():
        illness = illness_entry.get()
        cursor.execute("SELECT * FROM prescriptions WHERE illness=?", (illness,))
        result = cursor.fetchall()
        if result:
            status_label["text"] = f"Found {len(result)} illness(es)."
        else:
            status_label["text"] = "Not found."

    # Function to delete an illness
    def delete_illness():
        illness = illness_entry.get()
        cursor.execute("DELETE FROM prescriptions WHERE illness=?", (illness,))
        conn.commit()
        status_label["text"] = "Prescription deleted successfully."

    # Function to update a drug for an illness
    def update_illness():
        illness = illness_entry.get()
        drug = drug_entry.get()
        cursor.execute("UPDATE prescriptions SET drug=? WHERE illness=?", (drug, illness))
        conn.commit()
        status_label["text"] = "Prescription updated successfully."

    # Function to display the entire illness table
    def display_illness_table():
        cursor.execute("SELECT * FROM prescriptions")
        result = cursor.fetchall()
        if result:
            messagebox.showinfo("Prescription List", "\n".join(str(row) for row in result))
        else:
            messagebox.showinfo("Prescription List", "No illnesses found.")

    illness_label = Label(illness_table_window, text="Illness:")
    illness_label.pack()
    illness_entry = Entry(illness_table_window)
    illness_entry.pack()

    drug_label = Label(illness_table_window, text="Prescription:")
    drug_label.pack()
    drug_entry = Entry(illness_table_window)
    drug_entry.pack()

    insert_button = Button(illness_table_window, text="Insert", command=insert_illness)
    insert_button.pack()

    search_button = Button(illness_table_window, text="Search", command=search_illness)
    search_button.pack()
    
    update_button = Button(illness_table_window, text="Update", command=update_illness)
    update_button.pack()

    delete_button = Button(illness_table_window, text="Delete", command=delete_illness)
    delete_button.pack()
    
    display_button = Button(illness_table_window, text="Display Table", command=display_illness_table)
    display_button.pack()

    status_label = Label(illness_table_window, text="")
    status_label.pack()

# Function to display the join of patient and illness tables
def display_join():
    cursor.execute("SELECT patients.name, patients.age, prescriptions.illness, prescriptions.drug "
                   "FROM patients INNER JOIN prescriptions ON patients.illness = prescriptions.illness")
    result = cursor.fetchall()
    if result:
        messagebox.showinfo("Joint Data", "\n".join(str(row) for row in result))
    else:
        messagebox.showinfo("Joint Data", "No matching records found.")

# Main window setup
root = Tk()
root.title("Mental Ward Database")

patient_records_button = Button(root, text="Patient Records", command=open_patient_records_window)
patient_records_button.pack()

illness_table_button = Button(root, text="Prescription Records", command=open_illness_table_window)
illness_table_button.pack()

join_button = Button(root, text="Display Join", command=display_join)
join_button.pack()

root.mainloop()

# Close the database connection
conn.close()
