<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<h2>Exchange key</h2>
<p>This action requires validation.  Paste the key ASCII-armored below:</p>
<form action="import_key.rb" method="post">
  <table>
  <tr>
    <td><label>Your key ID</label></td>
    <td><input type="text" name="signer_id" /></td>
  </tr>
  <tr>
    <td><label>The signed key of the other party</label></td>
    <td><textarea cols=78 rows=20 name="key"></textarea></td>
  </tr>
  <tr>
    <td><input type="submit" value="Exchange" /></td>
  <tr>
  </table>
</form>
