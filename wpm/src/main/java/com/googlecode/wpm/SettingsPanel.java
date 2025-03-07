package com.googlecode.wpm;

import java.awt.Desktop;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;

/**
 * Settings
 */
public class SettingsPanel extends javax.swing.JPanel {
    /** 
     * Creates new form SettingsPanel
     */
    public SettingsPanel() {
        initComponents();
        URL url = Repository.getLocation();
        String t;
        if (url == null)
            t = "";
        else
            t = url.toExternalForm();

        jTextFieldRepository.setText(t);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jTextFieldRepository = new javax.swing.JTextField();
        jButtonSave = new javax.swing.JButton();
        jLabelURL = new javax.swing.JLabel();

        jLabel1.setLabelFor(jTextFieldRepository);
        jLabel1.setText("Repository:");

        jTextFieldRepository.setToolTipText("Enter your repository URL here");

        jButtonSave.setText("Save");
        jButtonSave.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonSaveActionPerformed(evt);
            }
        });

        jLabelURL.setText("<html>You can find the list of available repositories at <br>\n<a href=\"http://code.google.com/p/windows-package-manager/\">http://code.google.com/p/windows-package-manager/</a></html>");
        jLabelURL.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        jLabelURL.setDoubleBuffered(true);
        jLabelURL.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jLabelURLMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jTextFieldRepository, javax.swing.GroupLayout.DEFAULT_SIZE, 440, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jButtonSave))
            .addGroup(layout.createSequentialGroup()
                .addComponent(jLabelURL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(jTextFieldRepository, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jButtonSave)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabelURL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(217, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jButtonSaveActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonSaveActionPerformed
        String s = jTextFieldRepository.getText().trim();
        try {
            Repository.setLocation(new URL(s));
        } catch (MalformedURLException ex) {
            App.informUser(ex);
            Repository.setLocation(null);
        }
        firePropertyChange("repositoryLocation", null, null);
    }//GEN-LAST:event_jButtonSaveActionPerformed

    private void jLabelURLMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jLabelURLMouseClicked
        if (Desktop.isDesktopSupported()) {
            Desktop d = Desktop.getDesktop();
            try {
                d.browse(new URI("http://code.google.com/p/windows-package-manager/"));
            } catch (URISyntaxException ex) {
                App.unexpectedWarn(ex);
            } catch (IOException ex) {
                App.unexpectedWarn(ex);
            }
        }
    }//GEN-LAST:event_jLabelURLMouseClicked


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButtonSave;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabelURL;
    private javax.swing.JTextField jTextFieldRepository;
    // End of variables declaration//GEN-END:variables

}
